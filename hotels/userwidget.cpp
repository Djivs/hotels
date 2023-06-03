#include "userwidget.h"

UserWidget::UserWidget(SQLWorker *w) {
    worker = w;

    setupUi();
    setupWorker();
}

void UserWidget::setupUi() {
    exitButton = new QPushButton("Обратно");

    layout = new QVBoxLayout;
    layout->addWidget(exitButton);

    setLayout(layout);

    connect(exitButton, &QPushButton::clicked, this, [this] {
        emit exit();
    });
}

void UserWidget::setupWorker() {

}
