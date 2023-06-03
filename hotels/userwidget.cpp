#include "userwidget.h"

#include <QLabel>
#include <QDebug>
#include <QCompleter>

UserWidget::UserWidget(SQLWorker *w) {
    worker = w;

    setupUi();
    setupWorker();

    emit getFreeRooms(QDate::currentDate(), QDate::currentDate());
    emit getGuests();
}

void UserWidget::setupUi() {


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
    layout->addWidget(new QLabel("Бронирование номеров"));

    layout->addWidget(new QLabel("Свободные номера:"));
    layout->addWidget(freeRoomsTable);
    layout->addLayout(guestLayout);
    layout->addLayout(roomLayout);
    layout->addLayout(calendarLayout);
    layout->addWidget(bookButton);
    layout->addWidget(exitButton);

    setLayout(layout);

    connect(exitButton, &QPushButton::clicked, this, [this] {
        emit exit();
    });

}

void UserWidget::setupWorker() {
    connect(this, &UserWidget::getFreeRooms, worker, &SQLWorker::getFreeRooms);
    connect(worker, &SQLWorker::getFreeRoomsReady, this, &UserWidget::processFreeRooms);

    connect(this, &UserWidget::getGuests, worker, &SQLWorker::getGuests);
    connect(worker, &SQLWorker::getGuestsReady, this, &UserWidget::processGuests);

    connect(calendar, &CalendarWidget::rangeChanged, this, [this] {emit getFreeRooms(calendar->getFromDate(), calendar->getToDate());});
}

void UserWidget::book() {

    const QPair<QDate, QDate> dateRange = calendar->getRange();
    const QString guest = guestName->text();
    const int roomNumber = roomBox->currentText().toInt();


    if (guest.isEmpty()) {
        qDebug() << "fill guests name first!";
        return;
    }
}

void UserWidget::processFreeRooms(QVector <QMap <QString, QVariant>> rooms) {
    roomBox->clear();
    freeRoomsModel->removeRows(0, freeRoomsModel->rowCount());
    freeRoomsModel->setRowCount(rooms.size());
    for (int i = 0; i < rooms.size(); ++i) {
        const auto room = rooms[i];

        freeRoomsModel->setData(freeRoomsModel->index(i, 0), room["hotel_name"]);
        freeRoomsModel->setData(freeRoomsModel->index(i, 1), room["kind"]);
        freeRoomsModel->setData(freeRoomsModel->index(i, 2), room["number"]);
        freeRoomsModel->setData(freeRoomsModel->index(i, 3), room["price"]);

        roomBox->addItem(room["number"].toString());
    }
}

void UserWidget::processGuests(QStringList guests) {
    guestName->setCompleter(new QCompleter(guests));
}
