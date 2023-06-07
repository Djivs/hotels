#include "totalprofitwidget.h"

#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>

TotalProfitWidget::TotalProfitWidget(SQLWorker *w)
{
    worker = w;

    setupFormHeader();
    setupWorker();
    setupUi();

    loadPage();
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

    connect(this, &TotalProfitWidget::getProfits, worker, &SQLWorker::getOverallHotelsProfits);
    connect(worker, &SQLWorker::getOverallHotelsProfitsReady, this, &TotalProfitWidget::processProfits);

}

void TotalProfitWidget::loadPage() {
    emit getProfits();
}

void TotalProfitWidget::processProfits(QVariantMap profits) {
    QBarSeries *series = new QBarSeries;

    QStringList hotels;
    int maxValue = 0;

    for (auto &i : profits.keys()) {
        const int value = profits[i].toInt();

        maxValue = std::max(maxValue, value);
        QBarSet *set = new QBarSet(i);
        *set << value;
        series->append(set);

        hotels << i;
    }

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Суммарные доходы отелей");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,maxValue);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(hotels);
    series->attachAxis(axisX);

    chartView->setChart(chart);
}
