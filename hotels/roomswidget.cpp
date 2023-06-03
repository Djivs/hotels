#include "roomswidget.h"

#include <QLabel>

RoomsWidget::RoomsWidget(SQLWorker *w) {
    worker = w;

    setupWorker();
    setupFormHeader();
    setupUi();
}

void RoomsWidget::loadPage() {

}
void RoomsWidget::setupWorker() {

}

void RoomsWidget::setupUi() {
    hotelBox = new QComboBox;
    roomNumberBox = new QSpinBox;
    cost = new QLineEdit;
    availability = new QCheckBox;
    kindBox = new QGroupBox;

    layout = new QVBoxLayout;
    layout->addWidget(formHeader);
    formHeader->setTitle("Номера");
    layout->addWidget(hotelBox);
    layout->addWidget(roomNumberBox);
    layout->addWidget(cost);
    layout->addWidget(availability);
    layout->addWidget(kindBox);

    setLayout(layout);

}
