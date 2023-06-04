#ifndef FREEROOMSWIDGET_H
#define FREEROOMSWIDGET_H

#include "formwidget.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class FreeRoomsWidget : public FormWidget
{
public:
    FreeRoomsWidget(SQLWorker *w);
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QLineEdit *searchHotel;
    QStandardItemModel *roomsModel;
    QTableView *roomsTable;
    QPushButton *save;
    QPushButton *leave;

    QHBoxLayout *searchLayout;



};

#endif // FREEROOMSWIDGET_H
