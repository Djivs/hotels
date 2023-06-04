#include "workerswidget.h"

WorkersWidget::WorkersWidget(SQLWorker *w)
{
    worker = w;

    setupFormHeader();
    setupWorker();
    setupUi();
}

void WorkersWidget::setupUi() {
    layout = new QVBoxLayout;
    layout->addWidget(formHeader);

    setLayout(layout);
}

void WorkersWidget::setupWorker() {

}

void WorkersWidget::loadPage() {

}
