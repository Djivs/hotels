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

class RoomsWidget : public FormWidget
{
public:
    RoomsWidget(SQLWorker *w);
private:
    void loadPage();
    void setupWorker();
    void setupUi();

    QComboBox *hotelBox;
    QSpinBox *roomNumberBox;
    QLineEdit *cost;
    QCheckBox *availability;
    QGroupBox *kindBox;
    QVector <QRadioButton *> kindButtons;

};

#endif // ROOMSWIDGET_H
