#include "mainwindow.h"

#include "loginwidget.h"
#include "userwidget.h"
#include "adminwidget.h"

#include <iostream>
#include <QDebug>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    worker = new SQLWorker;

    this->setMinimumSize(800, 700);


    setupLogin();
}

MainWindow::~MainWindow() {
    delete worker;
}

void MainWindow::setupLogin() {
    LoginWidget *loginWidget = new LoginWidget(worker);
    setCentralWidget(loginWidget);

    connect(loginWidget, &LoginWidget::userChecked, this, &MainWindow::processAuth);
}

void MainWindow::processAuth(int result) {
    if (!result) {
        AdminWidget *w = new AdminWidget(worker);
        setScrollWidget(w);

        connect(w, &AdminWidget::exit, this, [this] {
            setupLogin();
        });
    } else {
        UserWidget *w = new UserWidget(worker, result);
        setScrollWidget(w);

        connect(w, &UserWidget::exit, this, [this] {
            setupLogin();
        });
    }
}

void MainWindow::setScrollWidget(QWidget *w) {
    QScrollArea *mw = new QScrollArea();
    mw->setWidget(w);
    mw->setWidgetResizable(1);
    setCentralWidget(mw);
}

