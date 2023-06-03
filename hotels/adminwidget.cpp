#include "adminwidget.h"

#include <QLabel>

AdminWidget::AdminWidget(SQLWorker *w) {
    worker = w;

    setupUi();
}

void AdminWidget::setupUi() {
    exitButton = new QPushButton("Обратно");

    hotelsButton = new QPushButton("Отели");
    roomsButton = new QPushButton("Комнаты");
    workersButton = new QPushButton("Работники");
    guestsButton = new QPushButton("Гости");
    freeRoomsButton = new QPushButton("Свободные номера");
    totalProfitButton = new QPushButton("Суммарная выручка отелей");


    layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Меню администратора"));
    layout->addWidget(hotelsButton);
    layout->addWidget(roomsButton);
    layout->addWidget(workersButton);
    layout->addWidget(guestsButton);
    layout->addWidget(freeRoomsButton);
    layout->addWidget(totalProfitButton);
    layout->addWidget(exitButton);

    connect(exitButton, &QPushButton::clicked, this, [this] {emit exit();});

    connect(hotelsButton, &QPushButton::clicked, this, [this] {emit hotels();});
    connect(roomsButton, &QPushButton::clicked, this, [this] {emit rooms();});
    connect(workersButton, &QPushButton::clicked, this, [this] {emit workers();});
    connect(guestsButton, &QPushButton::clicked, this, [this] {emit guests();});
    connect(freeRoomsButton, &QPushButton::clicked, this, [this] {emit freeRooms();});
    connect(totalProfitButton, &QPushButton::clicked, this, [this] {emit totalProfit();});

    setLayout(layout);

}
