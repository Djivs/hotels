#include "workerswidget.h"

#include <QLabel>
#include <QComboBox>

WorkersWidget::WorkersWidget(SQLWorker *w)
{
    worker = w;

    setupWorker();
    setupUi();

    loadPage();
}

void WorkersWidget::setupUi() {
    model = new QStandardItemModel;
    table = new QTableView;
    table->setModel(model);

    model->setColumnCount(header.size());
    model->setHorizontalHeaderLabels(header);
    
    add = new QPushButton("Добавить новую запись");

    connect(add, &QPushButton::clicked, this, &WorkersWidget::addNewWorker);

    save = new QPushButton("Сохранить изменения");

    leave = new QPushButton("Обратно");

    layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Работники"));
    layout->addWidget(table);
    layout->addWidget(add);
    layout->addWidget(save);
    layout->addWidget(leave);

    setLayout(layout);

    connect(save, &QPushButton::clicked, this, &WorkersWidget::saveWorkers);
    connect(leave, &QPushButton::clicked, this, [this] {emit exit();});
}

void WorkersWidget::setupWorker() {
    connect(this, &WorkersWidget::getHotels, worker, &SQLWorker::getHotels);
    connect(worker, &SQLWorker::getHotelsReady, this, &WorkersWidget::processHotels);
    connect(this, &WorkersWidget::getWorkers, worker, &SQLWorker::getWorkers);
    connect(worker, &SQLWorker::getWorkersReady, this, &WorkersWidget::processWorkersData);

    connect(this, &WorkersWidget::updateWorker, worker, &SQLWorker::updateWorker);
    connect(this, &WorkersWidget::insertWorker, worker, &SQLWorker::insertWorker);
}

void WorkersWidget::loadPage() {
    emit getHotels();
    emit getWorkers();
}

void WorkersWidget::processHotels(QStringList _hotels) {
    hotels = _hotels;
}
void WorkersWidget::processWorkersData(QVector<QVariantMap> workers) {
    workersAmount = workers.size();
    
    model->removeRows(0, model->rowCount());
    model->setRowCount(workers.size());

    for (int i = 0; i < workers.size(); ++i) {
        QComboBox *box = new QComboBox;
        for (auto &i : hotels) {
            box->addItem(i);
        }

        for (int j = 0; j < box->count(); ++j) {
            if (box->itemText(j) == workers[i]["hotel"].toString()) {
                box->setCurrentIndex(j);
                break;
            }
        }

        table->setIndexWidget(model->index(i, 0), box);
        model->setData(model->index(i, 1), workers[i]["name"].toString());
        model->setData(model->index(i, 2), workers[i]["position"].toString());
    }

}

void WorkersWidget::addNewWorker() {
    model->insertRow(model->rowCount());

    QComboBox *box = new QComboBox;
    for (auto &i :hotels) {
        box->addItem(i);
    }

    table->setIndexWidget(model->index(model->rowCount() - 1, 0), box);
}

void WorkersWidget::saveWorkers() {
    for (int i = 0;i < workersAmount; ++i) {
        emit updateWorker(getWorkersMap(i));
    }
    for (int i = workersAmount; i < model->rowCount(); ++i) {
        emit insertWorker(getWorkersMap(i));
    }
}

QVariantMap WorkersWidget::getWorkersMap(int row) {
    QVariantMap worker;

    worker["hotel"] = dynamic_cast<QComboBox*>(table->indexWidget(model->index(row, 0)))->currentText();
    worker["name"] = model->data(model->index(row, 1));
    worker["position"] = model->data(model->index(row, 2));
    worker["id"] = row + 1;


    return worker;
}
