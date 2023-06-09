#ifndef FORMWIDGET_H
#define FORMWIDGET_H

#include "formheader.h"
#include "sqlworker.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QDebug>
#include <QPainter>
#include <QPrinter>
#include <QThread>
#include <QMessageBox>
#include <QStandardItemModel>

#define TABLE_CELL_SIZE 37

class FormWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FormWidget(QWidget *parent = nullptr);
protected:
    virtual void loadPage() = 0;
    virtual void setupWorker() = 0;
    virtual void setupUi() = 0;


    void setupFormHeader();
    void printPage();
    void resizeTableView(QTableView *v);
    void showSearchError();
    void showSaved();

    quint32 curInd = 1;

    SQLWorker *worker;
    FormHeader *formHeader;
    QVBoxLayout *layout;

signals:
    void exit();
    void setMaxInd();

};

#endif // FORMWIDGET_H
