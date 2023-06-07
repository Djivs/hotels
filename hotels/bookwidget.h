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
    explicit BookWidget(SQLWorker *w);
signals:
    void getFreeRooms(QDate from, QDate to);
    void getGuests();
    void exit();
    void book(int, int, QDate, QDate);
private slots:
    void processFreeRooms(QVector <QMap <QString, QVariant>> rooms);
    void processGuests(QStringList guests);
    void makeBooking();
private:
    void setupUi();
    void setupWorker();

    QPushButton *exitButton;

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

    QStringList header = {"Отель", "Тип", "Номер", "Цена"};
};

#endif // USERWIDGET_H
