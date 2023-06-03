#include "sqlworker.h"
#include <QDebug>
#include <QSqlError>

SQLWorker::SQLWorker(QObject *parent)
    : QObject{parent} {


    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("hotel");
    db.setUserName("postgres");
    db.setPassword("123");

    if (!db.open()) {
        qDebug() << "Can't open database.\nError:" << db.lastError().text();
    } else {
        qDebug() << "DB Connection established.";
    }

}
