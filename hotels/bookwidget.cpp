#include "bookwidget.h"

#include <QLabel>
#include <QDebug>
#include <QCompleter>
#include <QMessageBox>

BookWidget::BookWidget(SQLWorker *w, QString _hotelName) {
    hotelName = _hotelName;

    worker = w;

    setupUi();
    setupWorker();

    emit getFreeRooms(QDate::currentDate(), QDate::currentDate());
    emit getGuests();
    //emit getGuest(guestId);
}

void BookWidget::setupUi() {


    freeRoomsModel = new QStandardItemModel;
    freeRoomsTable = new QTableView;

    freeRoomsModel->setColumnCount(header.size());
    for (int i = 0; i < header.size(); ++i) {
        freeRoomsModel->setHeaderData(i, Qt::Horizontal, header[i]);
    }
    freeRoomsTable->setModel(freeRoomsModel);

    guestName = new QLineEdit;
    

    roomBox = new QComboBox;
    calendar = new CalendarWidget;

    bookButton = new QPushButton("Забронировать");
    exitButton = new QPushButton("Обратно");

    guestLayout = new QHBoxLayout;
    guestLayout->addWidget(new QLabel("Имя гостя:"));
    guestLayout->addWidget(guestName);

    roomLayout = new QHBoxLayout;
    roomLayout->addWidget(new QLabel("Номер:"));
    roomLayout->addWidget(roomBox);

    calendarLayout = new QHBoxLayout;
    calendarLayout->addWidget(new QLabel("Даты бронирования:"));
    calendarLayout->addWidget(calendar);

    layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Бронирование номеров в отеле " + hotelName));
    layout->addLayout(guestLayout);
    layout->addWidget(new QLabel("Свободные номера:"));
    layout->addWidget(freeRoomsTable);
    layout->addLayout(roomLayout);
    layout->addLayout(calendarLayout);
    layout->addWidget(bookButton);
    layout->addWidget(exitButton);

    setLayout(layout);

    connect(exitButton, &QPushButton::clicked, this, [this] {
        emit exit();
    });

}

void BookWidget::setupWorker() {
    connect(this, &BookWidget::getFreeRooms, worker, &SQLWorker::getFreeRooms);
    connect(worker, &SQLWorker::getFreeRoomsReady, this, &BookWidget::processFreeRooms);

    connect(this, &BookWidget::getGuests, worker, &SQLWorker::getGuests);
    connect(worker, &SQLWorker::getGuestsReady, this, &BookWidget::processGuests);

    // connect(this, &BookWidget::getGuest, worker, &SQLWorker::getGuest);
    // connect(worker, &SQLWorker::getGuestReady, this, &BookWidget::processGuest);

    connect(bookButton, &QPushButton::clicked, this, &BookWidget::makeBooking);
    connect(this, &BookWidget::book, worker, &SQLWorker::book);

    connect(calendar, &CalendarWidget::rangeChanged, this, [this] {emit getFreeRooms(calendar->getFromDate(), calendar->getToDate());});
}

void BookWidget::makeBooking() {

    const QPair<QDate, QDate> dateRange = calendar->getRange();
    const int roomNumber = roomBox->currentText().toInt();

    emit book(hotelName, guestName->text(), roomNumber, dateRange.first, dateRange.second);

    QMessageBox::information(this, "Бронирование", "Забронировано!");

    emit getFreeRooms(calendar->getFromDate(), calendar->getToDate());
}

void BookWidget::processFreeRooms(QVector <QMap <QString, QVariant>> rooms) {
    roomBox->clear();
    freeRoomsModel->removeRows(0, freeRoomsModel->rowCount());
    //freeRoomsModel->setRowCount(rooms.size());
    for (int i = 0; i < rooms.size(); ++i) {
        const auto room = rooms[i];

        const auto hotel = room["hotel"];

        if (hotel != hotelName) {
            continue;
        }
        const auto kind = room["kind"];
        const auto number = room["number"];
        const auto price = room["cost"];

        freeRoomsModel->insertRow(freeRoomsModel->rowCount());

        const int row = freeRoomsModel->rowCount() - 1;
        freeRoomsModel->setData(freeRoomsModel->index(row, 0), kind);
        freeRoomsModel->setData(freeRoomsModel->index(row, 1), number);
        freeRoomsModel->setData(freeRoomsModel->index(row, 2), price);

        roomBox->addItem(number.toString());
    }
}

void BookWidget::processGuests(QStringList guests) {
    guestName->setCompleter(new QCompleter(guests));
}

// void BookWidget::processGuest(QString name) {
//     guestName->setText(name);
// }
