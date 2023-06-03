#ifndef HOTELSWIDGET_H
#define HOTELSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "sqlworker.h"

class HotelsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HotelsWidget(SQLWorker *w);

signals:
    void exit();
private:
    void setupUi();

    QPushButton *exitButton;

    QVBoxLayout *layout;

    SQLWorker *worker;

};

#endif // HOTELSWIDGET_H
