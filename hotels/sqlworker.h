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
    void checkUserReady(int result);
    void getFreeRoomsReady(QVector <QMap <QString, QVariant>>);
    void getGuestsReady(QStringList);
    void getGuestReady(QString);
    void getHotelsReady(QStringList);
    void getKindsReady(QStringList);
    void getHotelRoomsDataReady(QVector <QVariantMap>);
    void getHotelProfitByRoomsReady(QVariantMap);
    void getRoomDataReady(QVariantMap);
    void getWorkerDataReady(QVariantMap);
    void getHotelDataReady(QVariantMap);
    void getGuestDataReady(QVariantMap);
    void getGuestBookingHistoryReady(QVector <QVariantMap>);
    void getOverallHotelsProfitsReady(QVariantMap);
    void getWorkersReady(QVector <QVariantMap>);
    void getGuestCredentialsReady(QVariantMap);
public slots:
    void book(QString hotel, QString guest, int roomNumber, QDate fromDate, QDate toDate);
    void checkUser(QString login, QString pass);
    void getFreeRooms(QDate from, QDate to);
    void getGuests();
    void getHotels();
    void getKinds();
    void getWorkers();
    void getGuest(int id);
    void getHotelData(int id);
    void getHotelRoomsData(int id);
    void getHotelProfitByRooms(int id);
    void getRoomData(int id);
    void getWorkerData(int id);
    void getGuestData(int id);
    void getGuestBookingHistory(int id);
    void getOverallHotelsProfits();
    void updateHotel(QVariantMap hotel);
    void insertHotel(QVariantMap hotel);
    void updateRoom(QVariantMap room);
    void insertRoom(QVariantMap room);
    void updateWorker(QVariantMap worker);
    void insertWorker(QVariantMap worker);
    void updateGuest(QVariantMap guest);
    void insertGuest(QVariantMap guest);
    void getGuestCredentials(int id);
    //void insertGuestCredentials(QVariantMap guest);
    //void updateGuestCredentials(QVariantMap guest);
private:
    QSqlDatabase db;



};

#endif // SQLWORKER_H
