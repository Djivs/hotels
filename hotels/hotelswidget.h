#ifndef HOTELSWIDGET_H
#define HOTELSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QTableView>

#include "sqlworker.h"
#include "formwidget.h"

class HotelsWidget : public FormWidget
{
    Q_OBJECT
public:
    explicit HotelsWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~HotelsWidget();
private:
    void setupWorker();
    void setupUi();

    void loadPage();

    QLineEdit *name;
    QLineEdit *site;
    QLineEdit *address;
    QLineEdit *phone;
    QStandardItemModel *roomsModel;
    QTableView *roomsTable;
    QPushButton *bookRoom;
    QPushButton *save;



};

#endif // HOTELSWIDGET_H
