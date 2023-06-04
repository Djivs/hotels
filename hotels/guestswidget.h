#ifndef GUESTSWIDGET_H
#define GUESTSWIDGET_H

#include "formwidget.h"

#include <QLineEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QHBoxLayout>
#include <QPushButton>

class GuestsWidget : public FormWidget
{
public:
    GuestsWidget(SQLWorker *w);
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QLineEdit *name;
    QLineEdit *passport;
    QLineEdit *phone;

    QStandardItemModel *bookingHistoryModel;
    QTableView *bookingHistoryTable;

    QHBoxLayout *nameLayout;
    QHBoxLayout *passportLayout;
    QHBoxLayout *phoneLayout;
    QHBoxLayout *bookingHistoryLayout;
    QPushButton *save;
};

#endif // GUESTSWIDGET_H
