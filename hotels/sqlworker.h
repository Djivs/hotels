#ifndef SQLWORKER_H
#define SQLWORKER_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>

class SQLWorker : public QObject
{
    Q_OBJECT
public:
    explicit SQLWorker(QObject *parent = nullptr);
signals:
    void checkUserReady(bool result);
    void getFreeRoomsReady(QVector <QMap <QString, QVariant>>);
public slots:
    void checkUser(QString login, QString pass);
    void getFreeRooms();
private:
    QSqlDatabase db;



};

#endif // SQLWORKER_H
