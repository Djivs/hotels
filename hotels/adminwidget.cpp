#include "adminwidget.h"

#include <QLabel>

AdminWidget::AdminWidget(SQLWorker *w) {
    worker = w;

    setupUi();
}

void AdminWidget::setupUi() {
    exitButton = new QPushButton("Обратно");

    layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Меню администратора"));
    layout->addWidget(exitButton);

    connect(exitButton, &QPushButton::clicked, this, [this] {emit exit();});

    setLayout(layout);

}
