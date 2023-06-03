#include "hotelswidget.h"

HotelsWidget::HotelsWidget(SQLWorker *w) {
    worker = w;
    setupUi();
}

void HotelsWidget::setupUi() {
    exitButton = new QPushButton("Обратно");

    layout = new QVBoxLayout;
    layout->addWidget(exitButton);

    setLayout(layout);

    connect(exitButton, &QPushButton::clicked, this, [this] {emit exit();});
}
