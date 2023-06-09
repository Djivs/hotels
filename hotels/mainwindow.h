#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sqlworker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void processAuth(int result);
private:
    void setupLogin();
    void setupAdmin();

    void setScrollWidget(QWidget *w);
    SQLWorker *worker;
};
#endif // MAINWINDOW_H
