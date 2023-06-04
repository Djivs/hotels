#ifndef ROOMSWIDGET_H
#define ROOMSWIDGET_H

#include "formwidget.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QRadioButton>
#include <QHBoxLayout>

class RoomsWidget : public FormWidget
{
    Q_OBJECT
public:
    RoomsWidget(SQLWorker *w);
signals:
    void getRoomData(int);
    void getKinds();
    void getHotels();
private slots:
    void processRoomData(QVariantMap room);
    void processKinds(QStringList kinds);
    void processHotels(QStringList hotels);
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QComboBox *hotelBox;
    QSpinBox *roomNumberBox;
    QLineEdit *cost;
    QCheckBox *availability;
    QGroupBox *kindBox;
    QPushButton *save;
    QVector <QRadioButton *> kindButtons;

    QHBoxLayout *hotelLayout;
    QHBoxLayout *kindLayout;
    QHBoxLayout *numberLayout;
    QHBoxLayout *costLayout;
    QHBoxLayout *availabilityLayout;

};

#endif // ROOMSWIDGET_H
