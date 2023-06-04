#ifndef GUESTSWIDGET_H
#define GUESTSWIDGET_H

#include "formwidget.h"

#include <QLineEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QHBoxLayout>
#include <QPushButton>

class GuestsWidget : public FormWidget {
    Q_OBJECT
public:
    GuestsWidget(SQLWorker *w);
signals:
    void getGuestData(int);
    void getGuestBookingHistory(int);
private slots:
    void processGuestData(QVariantMap);
    void processGuestBookingHistory(QVector<QVariantMap>);
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

    QStringList header = {"Название отеля", "Номер комнаты", "Вид номера", "Дата заезда", "Дата выезда"};


};

#endif // GUESTSWIDGET_H
