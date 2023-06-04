#include "guestswidget.h"

GuestsWidget::GuestsWidget(SQLWorker *w)
{
    worker = w;

    setupFormHeader();
    setupWorker();
    setupUi();
}

void GuestsWidget::setupUi() {
    layout = new QVBoxLayout;
    layout->addWidget(formHeader);

    setLayout(layout);
}

void GuestsWidget::setupWorker() {

}

void GuestsWidget::loadPage() {

}

