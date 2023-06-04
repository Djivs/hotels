#ifndef WORKERSWIDGET_H
#define WORKERSWIDGET_H

#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>

#include "formwidget.h"

class WorkersWidget : public FormWidget {
    Q_OBJECT
public:
    WorkersWidget(SQLWorker *w);
signals:
    void getHotels();
    void getWorkers();
private slots:
    void processHotels(QStringList hotels);
    void processWorkersData(QVector<QVariantMap>);
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QStandardItemModel *model;
    QTableView *table;
    QPushButton *save;
    QPushButton *leave;

    QStringList header = {"Отель", "ФИО Работника", "Должность"};
    QStringList hotels;
};

#endif // WORKERSWIDGET_H
