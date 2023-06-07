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

    connect(this, &RoomsWidget::updateRoom, worker, &SQLWorker::updateRoom);
    connect(this, &RoomsWidget::insertRoom, worker, &SQLWorker::insertRoom);
}

void RoomsWidget::setupUi() {
    hotelBox = new QComboBox;
    roomNumberBox = new QSpinBox;
    cost = new QSpinBox;
    availability = new QCheckBox;
    kindBox = new QGroupBox;
    save = new QPushButton("Сохранить");

    formHeader->setTitle("Номера");

    cost->setMaximum(1);
    roomNumberBox->setMaximum(1);

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
    layout->addLayout(hotelLayout);
    layout->addLayout(numberLayout);
    layout->addLayout(costLayout);
    layout->addLayout(availabilityLayout);
    layout->addLayout(kindLayout);
    layout->addWidget(save);

    setLayout(layout);

    connect(save, &QPushButton::clicked, this, &RoomsWidget::saveRoom);

}

void RoomsWidget::processRoomData(QVariantMap room) {
    isOutside = room.isEmpty();

    const QString hotelName = room["hotel"].toString();
    const QString kindName = room["kind"].toString();
    const int roomNumber = room["number"].toInt();
    const int costNumber = room["cost"].toInt();

    qDebug() << roomNumber << roomNumberBox->maximum();
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

    if (costNumber > cost->maximum()) {
        cost->setMaximum(costNumber);
    }

    if (roomNumber > roomNumberBox->maximum()) {
        roomNumberBox->setMaximum(roomNumber);
    }

    roomNumberBox->setValue(roomNumber);
    cost->setValue(room["cost"].toInt());

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

void RoomsWidget::saveRoom() {
    if (isOutside) {
        emit insertRoom(getCurrentRoomMap());
    } else {
        emit updateRoom(getCurrentRoomMap());
    }
}

QVariantMap RoomsWidget::getCurrentRoomMap() {
    QVariantMap room;

    room["id"] = curInd;
    room["hotel"] = hotelBox->currentText();
    room["number"] = roomNumberBox->value();
    room["cost"] = cost->value();
    room["availability"] = availability->isChecked();

    QString kind;
    for (int i = 0; i < kindButtons.size(); ++i) {
        if (kindButtons[i]->isChecked()) {
            kind = kindButtons[i]->text();
            break;
        }
    }
    room["kind"] = kind;

    return room;
}
