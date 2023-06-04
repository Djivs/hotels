#include "totalprofitwidget.h"

TotalProfitWidget::TotalProfitWidget(SQLWorker *w)
{
    worker = w;

    setupFormHeader();
    setupWorker();
    setupUi();
}

void TotalProfitWidget::setupUi() {
    layout = new QVBoxLayout;
    layout->addWidget(formHeader);

    setLayout(layout);
}

void TotalProfitWidget::setupWorker() {

}

void TotalProfitWidget::loadPage() {

}
