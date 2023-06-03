#include "mainwindow.h"

#include "loginwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    LoginWidget *loginWidget = new LoginWidget;
    setCentralWidget(loginWidget);
}

MainWindow::~MainWindow()
{
}

