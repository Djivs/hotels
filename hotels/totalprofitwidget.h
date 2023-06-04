#ifndef TOTALPROFITWIDGET_H
#define TOTALPROFITWIDGET_H

#include "formwidget.h"
#include <QPushButton>
#include <QChartView>

using QtCharts::QChart, QtCharts::QChartView;

class TotalProfitWidget : public FormWidget
{
public:
    TotalProfitWidget(SQLWorker *w);
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QChartView *chartView;
    QPushButton *leave;
};

#endif // TOTALPROFITWIDGET_H
