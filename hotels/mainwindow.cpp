// TODO: make setupUser();
#include "mainwindow.h"

#include "loginwidget.h"
#include "userwidget.h"
#include "adminwidget.h"
#include "hotelswidget.h"

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

void MainWindow::setupAdmin() {
    AdminWidget *w = new AdminWidget(worker);
    setScrollWidget(w);

    connect(w, &AdminWidget::exit, this, [this] {
        setupLogin();
    });

    connect(w, &AdminWidget::hotels, this, [this] {
        HotelsWidget *w = new HotelsWidget(worker);
        setScrollWidget(w);

        connect(w, &HotelsWidget::exit, this, [this] {
            setupAdmin();
        });
    });
}

void MainWindow::processAuth(int result) {
    if (!result) {
        setupAdmin();
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

