#ifndef HOTELSWIDGET_H
#define HOTELSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "sqlworker.h"
#include "formwidget.h"

class HotelsWidget : public FormWidget
{
    Q_OBJECT
public:
    explicit HotelsWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~HotelsWidget();
private:
    void loadPage() {}
    void connectWorker() {}
    void setupUi();

    QPushButton *exitButton;

};

#endif // HOTELSWIDGET_H
