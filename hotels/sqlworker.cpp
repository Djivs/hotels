#include "sqlworker.h"
#include <QDebug>
#include <QSqlError>
#include <QDate>

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

void SQLWorker::checkUser(QString login, QString password) {
    QSqlQuery query;
    query.prepare("select * from check_user(:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    query.exec();

    if (query.next()) {
        emit checkUserReady(query.value(0).toBool());
    } else {
        qDebug() << "Can't perform query.\nError:" << query.lastError().text();
    }
}

void SQLWorker::getFreeRooms(QDate from, QDate to) {
    QSqlQuery query;
    query.prepare("select * from get_free_rooms(:from_date, :to_date)");

    QString fromString = QString::number(from.year()) + '.' + QString::number(from.month()) + '.' + QString::number(from.day());
    QString toString = QString::number(to.year()) + '.' + QString::number(to.month()) + '.' + QString::number(to.day());


    query.bindValue(":from_date", fromString);
    query.bindValue(":to_date", toString);

    qDebug() << from << to;

    query.exec();
    QVector <QMap <QString, QVariant>> rooms;

    while (query.next()) {
        QMap <QString, QVariant> map;
        map["hotel_name"] = query.value(0);
        map["kind"] = query.value(1);
        map["number"] = query.value(2);
        map["price"] = query.value(3);
        rooms.push_back(map);
    }

    emit getFreeRoomsReady(rooms);

}

void SQLWorker::getGuests() {
    QSqlQuery query;
    query.prepare("select name from guest");

    query.exec();

    QStringList guests;

    while (query.next()) {
        guests << query.value(0).toString();
    }

    emit getGuestsReady(guests);
}
