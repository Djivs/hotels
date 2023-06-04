#include "totalprofitwidget.h"

TotalProfitWidget::TotalProfitWidget(SQLWorker *w)
{
    worker = w;

    setupFormHeader();
    setupWorker();
    setupUi();
}

void TotalProfitWidget::setupUi() {

    chartView = new QChartView;
    leave = new QPushButton("Обратно");


    layout = new QVBoxLayout;
    layout->addWidget(chartView);
    layout->addWidget(leave);
    setLayout(layout);

    connect(leave, &QPushButton::clicked, this, [this] {emit exit();});
}

void TotalProfitWidget::setupWorker() {

}

void TotalProfitWidget::loadPage() {

}
