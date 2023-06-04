#ifndef HOTELSWIDGET_H
#define HOTELSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QTableView>

#include "sqlworker.h"
#include "formwidget.h"

class HotelsWidget : public FormWidget
{
    Q_OBJECT
public:
    explicit HotelsWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~HotelsWidget();
signals:
    void getHotelData(int);
    void getHotelRooms(int);
private slots:
    void processHotelData(QMap <QString, QVariant> hotel);
    void processHotelRooms(QVector <QMap <QString, QVariant>> rooms);
private:
    void setupWorker();
    void setupUi();

    void loadPage();

    QLineEdit *name;
    QLineEdit *site;
    QLineEdit *address;
    QLineEdit *phone;
    QStandardItemModel *roomsModel;
    QTableView *roomsTable;
    QPushButton *bookRoom;
    QPushButton *save;

    QStringList header = {"Вид номера", "Номер комнаты", "Стоимость", "Доступность"};

};

#endif // HOTELSWIDGET_H
