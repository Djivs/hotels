#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "sqlworker.h"

class AdminWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdminWidget(SQLWorker *w);

signals:
    void exit();
    void hotels();
    void rooms();
    void workers();
    void guests();
    void freeRooms();
    void totalProfit();
private:
    void setupUi();

    QPushButton *exitButton;
    QPushButton *hotelsButton;
    QPushButton *roomsButton;
    QPushButton *workersButton;
    QPushButton *guestsButton;
    QPushButton *freeRoomsButton;
    QPushButton *totalProfitButton;

    QVBoxLayout *layout;

    SQLWorker *worker;

};

#endif // ADMINWIDGET_H
