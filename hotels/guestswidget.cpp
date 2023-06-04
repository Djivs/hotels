#include "guestswidget.h"

#include <QLabel>

GuestsWidget::GuestsWidget(SQLWorker *w)
{
    worker = w;

    setupFormHeader();
    setupWorker();
    setupUi();
}

void GuestsWidget::setupUi() {
    name = new QLineEdit;
    passport = new QLineEdit;
    phone = new QLineEdit;

    bookingHistoryModel = new QStandardItemModel;
    bookingHistoryTable = new QTableView;
    bookingHistoryTable->setModel(bookingHistoryModel);

    save = new QPushButton("Сохранить");

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

}

void GuestsWidget::loadPage() {

}

