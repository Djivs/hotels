#include "mainwindow.h"

#include "loginwidget.h"

#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    worker = new SQLWorker;

    LoginWidget *loginWidget = new LoginWidget(worker);
    setCentralWidget(loginWidget);

    connect(loginWidget, &LoginWidget::userChecked, this, &MainWindow::processAuth);
}

MainWindow::~MainWindow() {
    delete worker;
}

void MainWindow::processAuth(QString login) {
    if (login == "admin") {
        std::cout << "admin\n";
    } else if (login == "user") {
        std::cout << "user\n";
    }
}

