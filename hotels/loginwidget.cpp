#include "loginwidget.h"

#include <QLabel>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent} {
    auth = new QPushButton("Войти");

    login = new QLineEdit;
    pass = new QLineEdit;

    loginLayout = new QHBoxLayout;
    loginLayout->addWidget(new QLabel("Логин:"));
    loginLayout->addWidget(login);

    passLayout = new QHBoxLayout;
    passLayout->addWidget(new QLabel("Пароль:"));
    passLayout->addWidget(pass);

    layout = new QVBoxLayout;
    layout->addWidget(new QLabel("АИС Отеля"));
    layout->addLayout(loginLayout);
    layout->addLayout(passLayout);
    layout->addWidget(auth);


    setLayout(layout);

}
