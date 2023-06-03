#include "userwidget.h"

#include <QLabel>

UserWidget::UserWidget(SQLWorker *w) {
    worker = w;

    setupUi();
    setupWorker();
}

void UserWidget::setupUi() {


    freeRoomsModel = new QStandardItemModel;
    freeRoomsTable = new QTableView;
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

}
