#include "loginwidget.h"

#include <QLabel>

LoginWidget::LoginWidget(SQLWorker *w) {
    worker = w;

    setupUi();
    setupWorker();

}

void LoginWidget::setupUi() {
    auth = new QPushButton("Войти");

    login = new QLineEdit;
    password = new QLineEdit;

    loginLayout = new QHBoxLayout;
    loginLayout->addWidget(new QLabel("Логин:"));
    loginLayout->addWidget(login);

    passLayout = new QHBoxLayout;
    passLayout->addWidget(new QLabel("Пароль:"));
    passLayout->addWidget(password);

    layout = new QVBoxLayout;
    layout->addWidget(new QLabel("АИС Отеля"));
    layout->addLayout(loginLayout);
    layout->addLayout(passLayout);
    layout->addWidget(auth);


    setLayout(layout);
}

void LoginWidget::setupWorker() {
    connect(auth, &QPushButton::clicked, this, [this] {
        emit checkUser(login->text(), password->text());
    });

    connect(this, &LoginWidget::checkUser, worker, &SQLWorker::checkUser);
    connect(worker, &SQLWorker::checkUserReady, this, &LoginWidget::processAuthResults);
}

void LoginWidget::processAuthResults(int result) {
    if (result >= 0) {
        emit userChecked(result);
    }
}
