//TODO: choose room's hotel
#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QComboBox>
#include <QDate>

#include "sqlworker.h"
#include "calendarwidget.h"

class BookWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BookWidget(SQLWorker *w, QString _hotelName);
signals:
    void getFreeRooms(QDate from, QDate to);
    void getGuests();
    void exit();
    void book(QString, QString, int, QDate, QDate);
private slots:
    void processFreeRooms(QVector <QMap <QString, QVariant>> rooms);
    void processGuests(QStringList guests);
    void makeBooking();
private:
    void setupUi();
    void setupWorker();

    QStandardItemModel *freeRoomsModel;
    QTableView *freeRoomsTable;

    QLineEdit *guestName;
    QComboBox *roomBox;
    CalendarWidget *calendar;

    QPushButton *bookButton;

    QHBoxLayout *guestLayout;
    QHBoxLayout *roomLayout;
    QHBoxLayout *calendarLayout;
    QVBoxLayout *layout;

    SQLWorker *worker;

    QStringList header = {"Тип", "Номер", "Цена"};

    QString hotelName;
};

#endif // USERWIDGET_H
