#ifndef FREEROOMSWIDGET_H
#define FREEROOMSWIDGET_H

#include "formwidget.h"
#include "calendarwidget.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class FreeRoomsWidget : public FormWidget {
    Q_OBJECT
public:
    FreeRoomsWidget(SQLWorker *w);
signals:
    void getFreeRooms(QDate from, QDate to);
private slots:
    void processFreeRooms(QVector <QVariantMap>);
    void processSearch(const QString&);
    void goBack(bool checked);
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QLineEdit *searchHotel;
    QStandardItemModel *roomsModel;
    QTableView *roomsTable;
    QPushButton *save;
    QPushButton *leave;
    CalendarWidget *calendar;
    

    QHBoxLayout *searchLayout;

    QStringList header = {"Отель", "Тип номера", "Номер комнаты", "Стоимость"};



};

#endif // FREEROOMSWIDGET_H
