#ifndef WORKERSWIDGET_H
#define WORKERSWIDGET_H

#include "formwidget.h"

class WorkersWidget : public FormWidget
{
public:
    WorkersWidget(SQLWorker *w);
private:
    void loadPage();
    void setupWorker();
    void setupUi();
};

#endif // WORKERSWIDGET_H
