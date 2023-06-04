#ifndef TOTALPROFITWIDGET_H
#define TOTALPROFITWIDGET_H

#include "formwidget.h"

class TotalProfitWidget : public FormWidget
{
public:
    TotalProfitWidget(SQLWorker *w);
private:
    void loadPage();
    void setupWorker();
    void setupUi();
};

#endif // TOTALPROFITWIDGET_H
