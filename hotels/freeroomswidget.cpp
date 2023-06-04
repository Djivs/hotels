#include "freeroomswidget.h"

#include <QLabel>

FreeRoomsWidget::FreeRoomsWidget(SQLWorker *w)
{
    worker = w;

    setupWorker();
    setupUi();
}

void FreeRoomsWidget::setupUi() {
    searchHotel = new QLineEdit;

    roomsModel = new QStandardItemModel;
    roomsTable = new QTableView;
    roomsTable->setModel(roomsModel);

    save = new QPushButton("Сохранить");
    leave = new QPushButton("Обратно");

    searchLayout = new QHBoxLayout;
    searchLayout->addWidget(new QLabel("Поиск по названию отеля"));


    layout = new QVBoxLayout;
    layout->addLayout(searchLayout);
    layout->addWidget(roomsTable);
    layout->addWidget(save);
    layout->addWidget(leave);
    setLayout(layout);

    connect(leave, &QPushButton::clicked, this, [this] {emit exit();});
}

void FreeRoomsWidget::setupWorker() {

}

void FreeRoomsWidget::loadPage() {

}
