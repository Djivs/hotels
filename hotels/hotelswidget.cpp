#include "hotelswidget.h"

#include <QLabel>

#include "bookwidget.h"

HotelsWidget::HotelsWidget(SQLWorker *w, FormWidget *parent) :
FormWidget{parent} {
    worker = w;

    setupFormHeader();
    setupWorker();

    setupUi();

    loadPage();
}

HotelsWidget::~HotelsWidget() {

}

void HotelsWidget::setupUi() {
    formHeader->setTitle("Отели");

    name = new QLineEdit;
    site = new QLineEdit;
    address = new QLineEdit;
    phone = new QLineEdit;

    formHeader->setTitle("Отели");

    roomsModel = new QStandardItemModel;
    roomsModel->setColumnCount(header.size());
    roomsModel->setHorizontalHeaderLabels(header);
    roomsTable = new QTableView;
    roomsTable->setModel(roomsModel);

    bookRoom = new QPushButton("Оформить бронь");
    save = new QPushButton("Сохранить");

    connect(save, &QPushButton::clicked,this, &HotelsWidget::saveHotel);
    connect(bookRoom, &QPushButton::clicked, this, &HotelsWidget::openBookingWidget);

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
    connect(this, &HotelsWidget::getHotelData, worker, &SQLWorker::getHotelData);
    connect(worker, &SQLWorker::getHotelDataReady, this, &HotelsWidget::processHotelData);
    connect(this, &HotelsWidget::getHotelRooms, worker, &SQLWorker::getHotelRoomsData);
    connect(worker, &SQLWorker::getHotelRoomsDataReady, this, &HotelsWidget::processHotelRooms);

    connect(this, &HotelsWidget::updateHotel, worker, &SQLWorker::updateHotel);
    connect(this, &HotelsWidget::insertHotel, worker, &SQLWorker::insertHotel);
}

void HotelsWidget::loadPage() {
    emit getHotelData(curInd);
    emit getHotelRooms(curInd);
}

void HotelsWidget::processHotelData(QMap <QString, QVariant> hotel) {
    isOutside = hotel.isEmpty();

    name->setText(hotel["name"].toString());
    site->setText(hotel["site"].toString());
    address->setText(hotel["address"].toString());
    phone->setText(hotel["phone"].toString());
}

void HotelsWidget::processHotelRooms(QVector <QMap <QString, QVariant>> rooms) {
    roomsModel->removeRows(0, roomsModel->rowCount());

    roomsModel->setRowCount(rooms.size());

    for (int i = 0; i < rooms.size(); ++i) {
        roomsModel->setData(roomsModel->index(i, 0), rooms[i]["kind"]);
        roomsModel->setData(roomsModel->index(i, 1), rooms[i]["number"]);
        roomsModel->setData(roomsModel->index(i, 2), rooms[i]["cost"]);
        roomsModel->setData(roomsModel->index(i, 3), rooms[i]["availability"]);
    }
    roomsTable->show();
    roomsTable->update();
}

void HotelsWidget::saveHotel() {
    const QVariantMap hotel = getCurrentHotelMap();
    if (isOutside) {
        emit insertHotel(hotel);
    } else {
        emit updateHotel(hotel);
    }
}

QVariantMap HotelsWidget::getCurrentHotelMap() {
    QVariantMap hotel;

    hotel["name"] = name->text();
    hotel["site"] = site->text();
    hotel["address"] = address->text();
    hotel["phone"] = phone->text();
    hotel["id"] = curInd;

    return hotel;
}

void HotelsWidget::openBookingWidget() {
    BookWidget *w = new BookWidget(worker, name->text());

    w->show();

    w->setAttribute(Qt::WA_DeleteOnClose);
}
