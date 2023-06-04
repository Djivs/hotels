#ifndef WORKERSWIDGET_H
#define WORKERSWIDGET_H

#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>

#include "formwidget.h"

class WorkersWidget : public FormWidget
{
public:
    WorkersWidget(SQLWorker *w);
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QStandardItemModel *model;
    QTableView *table;
    QPushButton *save;

    QStringList header = {"Отель", "ФИО Работника", "Должность"};
};

#endif // WORKERSWIDGET_H
