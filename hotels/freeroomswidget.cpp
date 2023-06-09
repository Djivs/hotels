#include "freeroomswidget.h"

#include <QLabel>
#include <QFileDialog>

FreeRoomsWidget::FreeRoomsWidget(SQLWorker *w)
{
    worker = w;

    setupWorker();
    setupUi();

    loadPage();
}

void FreeRoomsWidget::setupUi() {
    searchHotel = new QLineEdit;

    connect(searchHotel, &QLineEdit::textChanged, this, &FreeRoomsWidget::processSearch);

    roomsModel = new QStandardItemModel;
    roomsModel->setHorizontalHeaderLabels(header);
    roomsModel->setColumnCount(header.size());

    roomsTable = new QTableView;
    roomsTable->setModel(roomsModel);

    calendar = new CalendarWidget;

    connect(calendar, &CalendarWidget::rangeChanged, this, &FreeRoomsWidget::loadPage);

    save = new QPushButton("Сохранить");
    printButton = new QPushButton("Распечатать");
    leave = new QPushButton("Обратно");

    searchLayout = new QHBoxLayout;
    searchLayout->addWidget(new QLabel("Поиск по названию отеля"));
    searchLayout->addWidget(searchHotel);


    layout = new QVBoxLayout;
    layout->addLayout(searchLayout);
    layout->addWidget(roomsTable);
    layout->addWidget(calendar);
    layout->addWidget(printButton);
    //layout->addWidget(save);
    layout->addWidget(leave);
    setLayout(layout);

    connect(leave, &QPushButton::clicked, this, &FreeRoomsWidget::goBack);
    connect(printButton, &QPushButton::clicked, this, &FreeRoomsWidget::print);
}

void FreeRoomsWidget::goBack(bool checked) {
    emit exit();
}

void FreeRoomsWidget::setupWorker() {
    connect(this, &FreeRoomsWidget::getFreeRooms, worker, &SQLWorker::getFreeRooms);
    connect(worker, &SQLWorker::getFreeRoomsReady, this, &FreeRoomsWidget::processFreeRooms);
}

void FreeRoomsWidget::loadPage() {
    emit getFreeRooms(calendar->getFromDate(), calendar->getToDate());
}

void FreeRoomsWidget::processFreeRooms(QVector<QVariantMap> rooms) {

    roomsModel->removeRows(0, roomsModel->rowCount());
    roomsModel->setRowCount(rooms.size());

    for (int i = 0; i < rooms.size(); ++i) {
        const QVariantMap room = rooms[i];

        const auto hotel = room["hotel"];
        const auto kind = room["kind"];
        const auto number = room["number"];
        const auto cost = room["cost"];
        const auto availability = room["availability"];

        roomsModel->setData(roomsModel->index(i, 0), hotel);
        roomsModel->setData(roomsModel->index(i, 1), kind);
        roomsModel->setData(roomsModel->index(i, 2), number);
        roomsModel->setData(roomsModel->index(i, 3), cost);
        roomsModel->setData(roomsModel->index(i, 4), availability);
    }
}

void FreeRoomsWidget::processSearch(const QString& searchingFor) {
    
    for (int i = 0; i < roomsModel->rowCount(); ++i) {
        const QString currentHotel = roomsModel->data(roomsModel->index(i, 0)).toString();

        if (!currentHotel.startsWith(searchingFor)) {
            roomsTable->hideRow(i);
        } else {
            roomsTable->showRow(i);
        }
    }
}

void FreeRoomsWidget::print() {
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(QFileDialog::getSaveFileName());
    printer.setFullPage(true);

    QPainter painter(&printer);


    double xscale = printer.pageRect(QPrinter::DevicePixel).width() / double(this->width());
    double yscale = printer.pageRect(QPrinter::DevicePixel).height() / double(this->height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect(QPrinter::DevicePixel).center());
    painter.scale(scale, scale);
    painter.translate(-this->width()/ 2, -this->height()/ 2);

    this->render(&painter);
}