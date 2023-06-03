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
private:
    QSqlDatabase db;

};

#endif // SQLWORKER_H
