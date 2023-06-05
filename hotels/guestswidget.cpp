#include "guestswidget.h"

#include <QLabel>

GuestsWidget::GuestsWidget(SQLWorker *w)
{
    worker = w;

    setupFormHeader();
    setupWorker();
    setupUi();

    loadPage();
}

void GuestsWidget::setupUi() {
    name = new QLineEdit;
    passport = new QLineEdit;
    phone = new QLineEdit;

    bookingHistoryModel = new QStandardItemModel;
    bookingHistoryModel->setHorizontalHeaderLabels(header);
    bookingHistoryModel->setColumnCount(header.size());
    bookingHistoryTable = new QTableView;
    bookingHistoryTable->setModel(bookingHistoryModel);

    save = new QPushButton("Сохранить");

    connect(save, &QPushButton::clicked, this, &GuestsWidget::saveGuest);

    nameLayout = new QHBoxLayout;
    nameLayout->addWidget(new QLabel("ФИО Гостя"));
    nameLayout->addWidget(name);

    passportLayout = new QHBoxLayout;
    passportLayout->addWidget(new QLabel("Паспортные данные"));
    passportLayout->addWidget(passport);

    phoneLayout = new QHBoxLayout;
    phoneLayout->addWidget(new QLabel("Номер телефона"));
    phoneLayout->addWidget(phone);

    bookingHistoryLayout = new QHBoxLayout;
    bookingHistoryLayout->addWidget(new QLabel("История бронирования"));
    bookingHistoryLayout->addWidget(bookingHistoryTable);

    layout = new QVBoxLayout;
    layout->addWidget(formHeader);
    layout->addLayout(nameLayout);
    layout->addLayout(passportLayout);
    layout->addLayout(phoneLayout);
    layout->addLayout(bookingHistoryLayout);
    layout->addWidget(save);

    setLayout(layout);
}

void GuestsWidget::setupWorker() {
    connect(this, &GuestsWidget::getGuestData, worker, &SQLWorker::getGuestData);
    connect(worker, &SQLWorker::getGuestDataReady, this, &GuestsWidget::processGuestData);
    connect(this, &GuestsWidget::getGuestBookingHistory, worker, &SQLWorker::getGuestBookingHistory);
    connect(worker, &SQLWorker::getGuestBookingHistoryReady, this, &GuestsWidget::processGuestBookingHistory);

    connect(this, &GuestsWidget::updateGuest, worker, &SQLWorker::updateGuest);
    connect(this, &GuestsWidget::insertGuest, worker, &SQLWorker::insertGuest);
}

void GuestsWidget::loadPage() {
    emit getGuestData(curInd);
    emit getGuestBookingHistory(curInd);
}

void GuestsWidget::processGuestData(QVariantMap guest) {
    isOutside = guest.isEmpty();
    name->setText(guest["name"].toString());
    passport->setText(guest["passport"].toString());
    phone->setText(guest["phone"].toString());
}
void GuestsWidget::processGuestBookingHistory(QVector<QVariantMap> bookings) {
    bookingHistoryModel->removeRows(0, bookingHistoryModel->rowCount());
    bookingHistoryModel->setRowCount(bookings.size());

    for (int i = 0; i < bookings.size(); ++i) {
        const auto booking = bookings[i];

        bookingHistoryModel->setData(bookingHistoryModel->index(i, 0), booking["hotel"]);
        bookingHistoryModel->setData(bookingHistoryModel->index(i, 1), booking["number"]);
        bookingHistoryModel->setData(bookingHistoryModel->index(i, 2), booking["kind"]);
        bookingHistoryModel->setData(bookingHistoryModel->index(i, 3), booking["fromDate"]);
        bookingHistoryModel->setData(bookingHistoryModel->index(i, 4), booking["toDate"]);
    }
}

void GuestsWidget::saveGuest() {
    const QVariantMap guest = currentGuestMap();

    if (isOutside) {
        emit insertGuest(guest);
    } else {
        emit updateGuest(guest);
    }
}

QVariantMap GuestsWidget::currentGuestMap() {
    QVariantMap guestMap;
    guestMap["id"] = curInd;
    guestMap["name"] = name->text();
    guestMap["passport"] = passport->text();
    guestMap["phone"] = phone->text();    

    return guestMap;
}

