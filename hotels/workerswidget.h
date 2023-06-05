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
    void updateWorker(QVariantMap);
    void insertWorker(QVariantMap);
private slots:
    void processHotels(QStringList hotels);
    void processWorkersData(QVector<QVariantMap>);

    void addNewWorker();
    void saveWorkers();
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QVariantMap getWorkersMap(int row);


    QStandardItemModel *model;
    QTableView *table;
    QPushButton *add;
    QPushButton *save;
    QPushButton *leave;

    QStringList header = {"Отель", "ФИО Работника", "Должность"};
    QStringList hotels;
    int workersAmount;
};

#endif // WORKERSWIDGET_H
