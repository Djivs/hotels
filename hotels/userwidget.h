#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "sqlworker.h"

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
    QVBoxLayout *layout;

    SQLWorker *worker;


};

#endif // USERWIDGET_H
