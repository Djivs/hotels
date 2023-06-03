#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
private:
    QPushButton *auth;
    QLineEdit *login;
    QLineEdit *pass;

    QHBoxLayout *loginLayout;
    QHBoxLayout *passLayout;
    QVBoxLayout *layout;

signals:

};

#endif // LOGINWIDGET_H
