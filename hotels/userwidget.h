#ifndef USERWIDGET_H
#define USERWIDGET_H

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

class UserWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserWidget(SQLWorker *w);
signals:
    void exit();
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


};

#endif // USERWIDGET_H
