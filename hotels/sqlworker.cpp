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
        emit checkUserReady(query.value(0).toInt());
    } else {
        qDebug() << "Can't perform query.\nError:" << query.lastError().text();
    }
}

void SQLWorker::getFreeRooms(QDate from, QDate to) {
    QSqlQuery query;
    query.prepare("select * from get_free_rooms(:from_date, :to_date)");

    query.bindValue(":from_date", from);
    query.bindValue(":to_date", to);

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

void SQLWorker::getGuest(int id) {
    QSqlQuery query;
    query.prepare("select name from guest where id = :id");
    query.bindValue(":id", id);

    query.exec();

    if (query.next()) {
        emit getGuestReady(query.value(0).toString());
    }

}

void SQLWorker::book(int guestId, int roomNumber, QDate fromDate, QDate toDate) {
    QSqlQuery query;
    query.prepare("select * from book(:guestId, :roomNumber, :fromDate, :toDate)");

    query.bindValue(":guestId", guestId);
    query.bindValue(":roomNumber", roomNumber);
    query.bindValue(":fromDate", fromDate);
    query.bindValue(":toDate", toDate);

    query.exec();
}

