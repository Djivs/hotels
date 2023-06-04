#include "roomswidget.h"

#include <QLabel>

RoomsWidget::RoomsWidget(SQLWorker *w) {
    worker = w;

    setupWorker();
    setupFormHeader();
    setupUi();

    emit getKinds();
    emit getHotels();

    loadPage();
}

void RoomsWidget::loadPage() {
    emit getRoomData(curInd);
}
void RoomsWidget::setupWorker() {
    connect(this, &RoomsWidget::getKinds, worker, &SQLWorker::getKinds);
    connect(worker, &SQLWorker::getKindsReady, this, &RoomsWidget::processKinds);
    connect(this, &RoomsWidget::getHotels, worker, &SQLWorker::getHotels);
    connect(worker, &SQLWorker::getHotelsReady, this, &RoomsWidget::processHotels);
    connect(this, &RoomsWidget::getRoomData, worker, &SQLWorker::getRoomData);
    connect(worker, &SQLWorker::getRoomDataReady, this, &RoomsWidget::processRoomData);
}

void RoomsWidget::setupUi() {
    hotelBox = new QComboBox;
    roomNumberBox = new QSpinBox;
    cost = new QLineEdit;
    availability = new QCheckBox;
    kindBox = new QGroupBox;
    save = new QPushButton("Сохранить");

    hotelLayout = new QHBoxLayout;
    hotelLayout->addWidget(new QLabel("Отель"));
    hotelLayout->addWidget(hotelBox);

    kindLayout = new QHBoxLayout;
    kindLayout->addWidget(new QLabel("Вид номера"));
    kindLayout->addWidget(kindBox);

    numberLayout = new QHBoxLayout;
    numberLayout->addWidget(new QLabel("Номер комнаты"));
    numberLayout->addWidget(roomNumberBox);

    costLayout = new QHBoxLayout;
    costLayout->addWidget(new QLabel("Стоимость"));
    costLayout->addWidget(cost);

    availabilityLayout = new QHBoxLayout;
    availabilityLayout->addWidget(new QLabel("Доступность"));
    availabilityLayout->addWidget(availability);

    layout = new QVBoxLayout;
    layout->addWidget(formHeader);
    formHeader->setTitle("Номера");
    layout->addLayout(hotelLayout);
    layout->addLayout(numberLayout);
    layout->addLayout(costLayout);
    layout->addLayout(availabilityLayout);
    layout->addLayout(kindLayout);
    layout->addWidget(save);

    setLayout(layout);

}

void RoomsWidget::processRoomData(QVariantMap room) {
    const auto hotelName = room["hotel"].toString();
    const auto kindName = room["kind"].toString();
    const auto roomNumber = room["number"].toInt();
    for (int i = 0; i < hotelBox->count(); ++i) {
        if (hotelBox->itemText(i) == hotelName) {
            hotelBox->setCurrentIndex(i);
            break;
        }
    }
    for (int i = 0; i < kindButtons.size(); ++i) {
        if (kindButtons[i]->text() == kindName) {
            kindButtons[i]->toggle();
        }
    }

    roomNumberBox->setValue(roomNumber);
    if (roomNumber > roomNumberBox->maximum()) {
        roomNumberBox->setMaximum(roomNumber + 1);
    }

    cost->setText(room["cost"].toString());
    availability->setChecked(room["availability"].toBool());


}
void RoomsWidget::processKinds(QStringList kinds) {
    for (int i = 0; i < kindButtons.size(); ++i) {
        delete kindButtons[i];
    }


    for (int i = 0; i < kinds.size(); ++i) {
        kindButtons.push_back(new QRadioButton(kinds[i]));
    }

    QVBoxLayout *l = new QVBoxLayout;
    for (auto &i : kindButtons) {
        l->addWidget(i);
    }

    kindBox->setLayout(l);
    kindBox->show();

}

void RoomsWidget::processHotels(QStringList hotels) {
    hotelBox->clear();
    for (auto &i : hotels) {
        hotelBox->addItem(i);
    }
}
