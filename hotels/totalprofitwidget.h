#ifndef TOTALPROFITWIDGET_H
#define TOTALPROFITWIDGET_H

#include "formwidget.h"
#include <QPushButton>
#include <QChartView>

class TotalProfitWidget : public FormWidget {
    Q_OBJECT
public:
    TotalProfitWidget(SQLWorker *w);
signals:
    void getProfits();
private slots:
    void processProfits(QVariantMap);
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QChartView *chartView;
    QPushButton *leave;
};

#endif // TOTALPROFITWIDGET_H
