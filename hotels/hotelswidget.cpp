#include "hotelswidget.h"

#include <QLabel>

HotelsWidget::HotelsWidget(SQLWorker *w, FormWidget *parent) :
FormWidget{parent} {
    worker = w;

    setupFormHeader();
    setupWorker();

    setupUi();
}

HotelsWidget::~HotelsWidget() {

}

void HotelsWidget::setupUi() {
    formHeader->setTitle("Отели");

    name = new QLineEdit;
    site = new QLineEdit;
    address = new QLineEdit;
    phone = new QLineEdit;

    roomsModel = new QStandardItemModel;
    roomsTable = new QTableView;
    roomsTable->setModel(roomsModel);

    bookRoom = new QPushButton("Оформить бронь");
    save = new QPushButton("Сохранить");

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(new QLabel("Название"));
    nameLayout->addWidget(name);

    QHBoxLayout *siteLayout = new QHBoxLayout;
    siteLayout->addWidget(new QLabel("Сайт"));
    siteLayout->addWidget(site);

    QHBoxLayout *addressLayout = new QHBoxLayout;
    addressLayout->addWidget(new QLabel("Адрес"));
    addressLayout->addWidget(address);

    QHBoxLayout *phoneLayout = new QHBoxLayout;
    phoneLayout->addWidget(new QLabel("Телефон"));
    phoneLayout->addWidget(phone);

    layout = new QVBoxLayout;
    layout->addWidget(formHeader);
    layout->addLayout(nameLayout);
    layout->addLayout(siteLayout);
    layout->addLayout(addressLayout);
    layout->addLayout(phoneLayout);
    layout->addWidget(new QLabel("Комнаты"));
    layout->addWidget(roomsTable);
    layout->addWidget(bookRoom);
    layout->addWidget(save);

    setLayout(layout);

}

void HotelsWidget::setupWorker() {


}

void HotelsWidget::loadPage() {

}
