#include "workerswidget.h"

#include "comboboxitemdelegate.h"

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

    ComboBoxItemDelegate *cbid = new ComboBoxItemDelegate(table);
    table->setItemDelegateForColumn(0, cbid);

    model->setColumnCount(header.size());
    model->setHorizontalHeaderLabels(header);

    save = new QPushButton("Сохранить изменения");
    leave = new QPushButton("Обратно");

    layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Работники"));
    layout->addWidget(table);
    layout->addWidget(save);
    layout->addWidget(leave);

    setLayout(layout);

    connect(leave, &QPushButton::clicked, this, [this] {emit exit();});
}

void WorkersWidget::setupWorker() {
    connect(this, &WorkersWidget::getHotels, worker, &SQLWorker::getHotels);
    connect(worker, &SQLWorker::getHotelsReady, this, &WorkersWidget::processHotels);
    connect(this, &WorkersWidget::getWorkers, worker, &SQLWorker::getWorkers);
    connect(worker, &SQLWorker::getWorkersReady, this, &WorkersWidget::processWorkersData);
}

void WorkersWidget::loadPage() {
    emit getHotels();
    emit getWorkers();
}

void WorkersWidget::processHotels(QStringList _hotels) {
    hotels = _hotels;
}
void WorkersWidget::processWorkersData(QVector<QVariantMap> workers) {
    model->removeRows(0, model->rowCount());
    model->setRowCount(workers.size());

    for (int i = 0; i < workers.size(); ++i) {
        QComboBox *box = new QComboBox;
        for (auto &i : hotels) {
            box->addItem(i);
        }

        for (int j = 0; j < box->count(); ++j) {
            if (box->itemText(j) == workers[i]["hotel"].toString()) {
                qDebug() << j;
                box->setCurrentIndex(j);
                break;
            }
        }

        table->setIndexWidget(model->index(i, 0), box);
        model->setData(model->index(i, 1), workers[i]["name"].toString());
        model->setData(model->index(i, 2), workers[i]["position"].toString());
    }

}
