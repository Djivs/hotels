#include "hotelswidget.h"

#include <QLabel>

HotelsWidget::HotelsWidget(SQLWorker *w, FormWidget *parent) :
FormWidget{parent} {
    worker = w;
    setupUi();
}

HotelsWidget::~HotelsWidget() {

}

void HotelsWidget::setupUi() {
    exitButton = new QPushButton("Обратно");

    formHeader = new FormHeader;

    layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Отели"));
    layout->addWidget(formHeader);
    layout->addWidget(exitButton);

    setLayout(layout);

    connect(exitButton, &QPushButton::clicked, this, [this] {emit exit();});

}
