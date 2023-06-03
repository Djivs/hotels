#include "mainwindow.h"

#include "loginwidget.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    worker = new SQLWorker;

    LoginWidget *loginWidget = new LoginWidget;
    setCentralWidget(loginWidget);
}

MainWindow::~MainWindow()
{
    delete worker;
}

