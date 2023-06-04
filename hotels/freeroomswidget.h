#ifndef FREEROOMSWIDGET_H
#define FREEROOMSWIDGET_H

#include "formwidget.h"

class FreeRoomsWidget : public FormWidget
{
public:
    FreeRoomsWidget(SQLWorker *w);
private:
    void loadPage();
    void setupWorker();
    void setupUi();
};

#endif // FREEROOMSWIDGET_H
