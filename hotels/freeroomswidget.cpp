#include "freeroomswidget.h"

FreeRoomsWidget::FreeRoomsWidget(SQLWorker *w)
{
    worker = w;

    setupFormHeader();
    setupWorker();
    setupUi();
}

void FreeRoomsWidget::setupUi() {
    layout = new QVBoxLayout;
    layout->addWidget(formHeader);

    setLayout(layout);
}

void FreeRoomsWidget::setupWorker() {

}

void FreeRoomsWidget::loadPage() {

}
