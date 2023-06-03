#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "sqlworker.h"
class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(SQLWorker *w);
signals:
    void checkUser(QString login, QString password);
    void userChecked(QString login);
private slots:
    void processAuthResults(bool result);
private:
    void setupUi();
    void setupWorker();

    QPushButton *auth;
    QLineEdit *login;
    QLineEdit *password;

    QHBoxLayout *loginLayout;
    QHBoxLayout *passLayout;
    QVBoxLayout *layout;

    SQLWorker *worker;

signals:

};

#endif // LOGINWIDGET_H
