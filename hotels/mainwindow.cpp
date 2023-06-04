// TODO: make setupUser();
#include "mainwindow.h"

#include "loginwidget.h"
#include "userwidget.h"
#include "adminwidget.h"
#include "hotelswidget.h"
#include "roomswidget.h"
#include "workerswidget.h"
#include "guestswidget.h"
#include "freeroomswidget.h"
#include "totalprofitwidget.h"


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

    connect(w, &AdminWidget::rooms, this, [this] {
        RoomsWidget *w = new RoomsWidget(worker);
        setScrollWidget(w);

        connect(w, &RoomsWidget::exit, this, [this] {
            setupAdmin();
        });
    });

    connect(w, &AdminWidget::guests, this, [this] {
        GuestsWidget *w = new GuestsWidget(worker);
        setScrollWidget(w);

        connect(w, &GuestsWidget::exit, this, [this] {
            setupAdmin();
        });
    });

    connect(w, &AdminWidget::workers, this, [this] {
        WorkersWidget *w = new WorkersWidget(worker);
        setScrollWidget(w);

        connect(w, &WorkersWidget::exit, this, [this] {
            setupAdmin();
        });
    });

    connect(w, &AdminWidget::freeRooms, this, [this] {
        FreeRoomsWidget *w = new FreeRoomsWidget(worker);
        setScrollWidget(w);

        connect(w, &FreeRoomsWidget::exit, this, [this] {
            setupAdmin();
        });
    });

    connect(w, &AdminWidget::totalProfit, this, [this] {
        TotalProfitWidget *w = new TotalProfitWidget(worker);
        setScrollWidget(w);

        connect(w, &RoomsWidget::exit, this, [this] {
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

