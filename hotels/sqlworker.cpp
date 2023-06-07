#include "sqlworker.h"
#include <QDebug>
#include <QSqlError>
#include <QDate>

SQLWorker::SQLWorker(QObject *parent)
    : QObject{parent} {


    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("hotels");
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
        map["hotel"] = query.value(0);
        map["kind"] = query.value(1);
        map["number"] = query.value(2);
        map["cost"] = query.value(3);
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

void SQLWorker::getHotels() {
    QSqlQuery query;
    query.prepare("select name from hotel");

    query.exec();

    QStringList hotels;

    while (query.next()) {
        hotels << query.value(0).toString();
    }

    emit getHotelsReady(hotels);
}

void SQLWorker::getHotelData(int id) {
    QSqlQuery query;
    query.prepare("select * from hotel where id = :id");

    query.bindValue(":id", id);

    query.exec();

    QVariantMap hotel;
    if (query.next()) {

        hotel["name"] = query.value(1);
        hotel["site"] = query.value(2);
        hotel["address"] = query.value(3);
        hotel["phone"] = query.value(4);
    } else {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }

    emit getHotelDataReady(hotel);
}
void SQLWorker::getHotelRoomsData(int id) {
    qDebug() << id;
    QSqlQuery query;
    query.prepare("select * from get_hotel_rooms(:id)");
    query.bindValue(":id", id);

    query.exec();

    QVector <QVariantMap> rooms;
    while (query.next()) {
        QVariantMap room;
        room["kind"] = query.value(0);
        room["number"] = query.value(1);
        room["cost"] = query.value(2);
        room["availability"] = query.value(3);
        rooms.push_back(room);
    }

    qDebug() << rooms;


    emit getHotelRoomsDataReady(rooms);
}
void SQLWorker::getHotelProfitByRooms(int id) {
    QSqlQuery query;
    query.prepare("select * from get_hotel_profit_by_rooms(:id)");
    query.bindValue(":id", id);

    query.exec();

    QVariantMap profitByRoom;
    while(query.next()) {
        profitByRoom[query.value(0).toString()] = query.value(1);
    }

    emit getHotelProfitByRoomsReady(profitByRoom);
}
void SQLWorker::getRoomData(int id) {
    QSqlQuery query;
    query.prepare("select * from get_room_data(:id)");
    query.bindValue(":id", id);

    query.exec();

    QVariantMap room;
    if(query.next()) {
        room["hotel"] = query.value(0);
        room["kind"] = query.value(1);
        room["number"] = query.value(2);
        room["cost"] = query.value(3);
        room["availability"] = query.value(4);
    }

    emit getRoomDataReady(room);
}
void SQLWorker::getWorkerData(int id) {
    QSqlQuery query;
    query.prepare("select * from worker_data(:id)");
    query.bindValue(":id", id);

    query.exec();

    QVariantMap worker;
    if (query.next()) {
        worker["hotel"] = query.value(0);
        worker["name"] = query.value(1);
        worker["position"] = query.value(2);
    }

    emit getWorkerDataReady(worker);
}
void SQLWorker::getGuestData(int id) {
    QSqlQuery query;
    query.prepare("select * from guest where id = :id");
    query.bindValue(":id", id);

    query.exec();

    QVariantMap guest;
    if (query.next()) {
        guest["name"] = query.value(1);
        guest["passport"] = query.value(2);
        guest["phone"] = query.value(3);
    }
    emit getGuestDataReady(guest);
}
void SQLWorker::getGuestBookingHistory(int id) {
    QSqlQuery query;
    query.prepare("select * from get_guest_booking_history(:id)");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }
    QVector <QVariantMap> bookings;
    while (query.next()) {
        QVariantMap booking;
        booking["number"] = query.value(0);
        booking["hotel"] = query.value(1);
        booking["fromDate"] = query.value(2);
        booking["toDate"] = query.value(3);
        booking["kind"] = query.value(4);
        bookings.push_back(booking);
    }

    emit getGuestBookingHistoryReady(bookings);
}
void SQLWorker::getOverallHotelsProfits() {
    QSqlQuery query;
    query.prepare("select * from get_overall_hotels_profits()");

    query.exec();

    QVariantMap hotelToProfit;
    while(query.next()) {
        hotelToProfit[query.value(0).toString()] = query.value(1);
    }

    emit getOverallHotelsProfitsReady(hotelToProfit);
}
void SQLWorker::updateHotel(QVariantMap hotel) {
    QSqlQuery query;
    query.prepare("update hotel set name = :name, site = :site, address = :address, phone = :phone where id = :id");

    query.bindValue(":name", hotel["name"]);
    query.bindValue(":site", hotel["site"]);
    query.bindValue(":address", hotel["address"]);
    query.bindValue(":phone", hotel["phone"]);
    query.bindValue(":id", hotel["id"]);

    query.exec();
}
void SQLWorker::insertHotel(QVariantMap hotel) {
    QSqlQuery query;
    query.prepare("insert into hotel values(:id, :name, :site, :address, :phone)");

    query.bindValue(":name", hotel["name"]);
    query.bindValue(":site", hotel["site"]);
    query.bindValue(":address", hotel["address"]);
    query.bindValue(":phone", hotel["phone"]);
    query.bindValue(":id", hotel["id"]);

    query.exec();
}
void SQLWorker::updateRoom(QVariantMap room) {
    int hotelId = -1, kindId = -1;

    QSqlQuery query;
    query.prepare("select id from hotel where name = :hotel_name");
    query.bindValue(":hotel_name", room["hotel"]);

    query.exec();

    if (query.next()) {
        hotelId = query.value(0).toInt();
    } else {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }

    query = QSqlQuery();
    query.prepare("select id from kinds_of_room where kind = :kind_name");
    query.bindValue(":kind_name", room["kind"]);

    query.exec();

    if (query.next()) {
        kindId = query.value(0).toInt();
    } else {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }

    query = QSqlQuery();
    query.prepare("update room set hotel_id = :hotel_id, kind_id = :kind_id, number = :number, price = :cost, availability = :availability where id = :id");

    query.bindValue(":hotel_id", hotelId);
    query.bindValue(":kind_id", kindId);
    query.bindValue(":number", room["number"]);
    query.bindValue(":cost", room["cost"]);
    query.bindValue(":availability", room["availability"]);
    query.bindValue(":id", room["id"]);

    if (!query.exec()) {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }



}
void SQLWorker::insertRoom(QVariantMap room) {
    int hotelId = -1, kindId = -1;

    QSqlQuery query;
    query.prepare("select id from hotel where name = :hotel_name");
    query.bindValue(":hotel_name", room["hotel"]);

    query.exec();

    if (query.next()) {
        hotelId = query.value(0).toInt();
    } else {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }

    query = QSqlQuery();
    query.prepare("select id from kinds_of_room where kind = :kind_name");
    query.bindValue(":kind_name", room["kind"]);

    query.exec();

    if (query.next()) {
        kindId = query.value(0).toInt();
    } else {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }

    query = QSqlQuery();
    query.prepare("insert into room values(:id, :hotel_id, :kind_id, :number, :cost, :availability)");

    query.bindValue(":hotel_id", hotelId);
    query.bindValue(":kind_id", kindId);
    query.bindValue(":number", room["number"]);
    query.bindValue(":cost", room["cost"]);
    query.bindValue(":availability", room["availability"]);
    query.bindValue(":id", room["id"]);

    query.exec();
}
void SQLWorker::updateWorker(QVariantMap worker) {
    int hotelId = -1;

    QSqlQuery query;
    query.prepare("select id from hotel where name = :hotel_name");
    query.bindValue(":hotel_name", worker["hotel"]);

    query.exec();

    if (query.next()) {
        hotelId = query.value(0).toInt();
    } else {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }

    query = QSqlQuery();
    query.prepare("update workers set hotel_id = :hotel_id, name = :name, position = :position where id = :id");

    query.bindValue(":hotel_id", hotelId);
    query.bindValue(":name", worker["name"]);
    query.bindValue(":position", worker["position"]);
    query.bindValue(":id", worker["id"]);

    if (!query.exec()) {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }
}
void SQLWorker::insertWorker(QVariantMap worker) {
    int hotelId = -1;

    QSqlQuery query;
    query.prepare("select id from hotel where name = :hotel_name");
    query.bindValue(":hotel_name", worker["hotel"]);

    query.exec();

    if (query.next()) {
        hotelId = query.value(0).toInt();
    }

    query = QSqlQuery();
    query.prepare("insert into workers values (:id, :hotel_id, :name, :position)");

    query.bindValue(":hotel_id", hotelId);
    query.bindValue(":name", worker["name"]);
    query.bindValue(":postition", worker["position"]);
    query.bindValue(":id", worker["id"]);

    if (!query.exec()) {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }
}
void SQLWorker::updateGuest(QVariantMap guest) {
    QSqlQuery query;
    query.prepare("update guest set name = :name, data = :passport, phone = :phone where id = :id");

    query.bindValue(":name", guest["name"]);
    query.bindValue(":passport", guest["passport"]);
    query.bindValue(":phone", guest["phone"]);
    query.bindValue(":id", guest["id"]);

    query.exec();

}
void SQLWorker::insertGuest(QVariantMap guest) {
    QSqlQuery query;
    query.prepare("insert into guest values(:id,:name,:passport, :phone)");

    query.bindValue(":name", guest["name"]);
    query.bindValue(":passport", guest["passport"]);
    query.bindValue(":phone", guest["phone"]);
    query.bindValue(":id", guest["id"]);

    query.exec();
}

void SQLWorker::getKinds() {
    QSqlQuery query;
    query.prepare("select kind from kinds_of_room");

    query.exec();

    QStringList kinds;

    while(query.next()) {
        kinds << query.value(0).toString();
    }

    emit getKindsReady(kinds);
}

void SQLWorker::getWorkers() {
    QSqlQuery query;
    query.prepare("select * from all_workers_data()");

    if (!query.exec()) {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError();
    }

    QVector <QVariantMap> workers;
    while (query.next()) {
        QVariantMap worker;
        worker["hotel"] = query.value(0);
        worker["name"] = query.value(1);
        worker["position"] = query.value(2);
        workers.push_back(worker);
    }

    emit getWorkersReady(workers);
}
