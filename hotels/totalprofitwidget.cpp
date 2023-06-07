#include "totalprofitwidget.h"

#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QFileDialog>

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
    printButton = new QPushButton("Распечатать отчёт");


    layout = new QVBoxLayout;
    layout->addWidget(chartView);
    layout->addWidget(printButton);
    layout->addWidget(leave);
    setLayout(layout);

    connect(leave, &QPushButton::clicked, this, [this] {emit exit();});
    connect(printButton, &QPushButton::clicked, this, &TotalProfitWidget::print);
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


void TotalProfitWidget::print() {
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(QFileDialog::getSaveFileName());
    printer.setFullPage(true);

    QPainter painter(&printer);


    double xscale = printer.pageRect(QPrinter::DevicePixel).width() / double(this->width());
    double yscale = printer.pageRect(QPrinter::DevicePixel).height() / double(this->height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect(QPrinter::DevicePixel).center());
    painter.scale(scale, scale);
    painter.translate(-this->width()/ 2, -this->height()/ 2);

    this->render(&painter);
}
