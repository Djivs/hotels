#ifndef GUESTSWIDGET_H
#define GUESTSWIDGET_H

#include "formwidget.h"

class GuestsWidget : public FormWidget
{
public:
    GuestsWidget(SQLWorker *w);
private:
    void loadPage();
    void setupWorker();
    void setupUi();
};

#endif // GUESTSWIDGET_H
