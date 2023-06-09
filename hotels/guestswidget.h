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
    void updateGuest(QVariantMap);
    void insertGuest(QVariantMap);
    void getGuestCredentials(int);
    void updateGuestCredentials(QVariantMap);
    void insertGuestCredentials(QVariantMap);
private slots:
    void processGuestData(QVariantMap);
    void processGuestBookingHistory(QVector<QVariantMap>);
    void processGuestCredentials(QVariantMap) {};
    void saveGuest();
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QVariantMap currentGuestMap();

    QLineEdit *name;
    QLineEdit *passport;
    QLineEdit *phone;
    QLineEdit *login;
    QLineEdit *password;

    QStandardItemModel *bookingHistoryModel;
    QTableView *bookingHistoryTable;

    QHBoxLayout *loginLayout;
    QHBoxLayout *passwordLayout;
    QHBoxLayout *nameLayout;
    QHBoxLayout *passportLayout;
    QHBoxLayout *phoneLayout;
    QHBoxLayout *bookingHistoryLayout;
    QPushButton *save;

    bool isOutside = false;

    QStringList header = {"Название отеля", "Номер комнаты", "Вид номера", "Дата заезда", "Дата выезда"};



};

#endif // GUESTSWIDGET_H
