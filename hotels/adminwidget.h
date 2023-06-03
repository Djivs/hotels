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
private:
    void setupUi();

    QPushButton *exitButton;

    QVBoxLayout *layout;

    SQLWorker *worker;

};

#endif // ADMINWIDGET_H
