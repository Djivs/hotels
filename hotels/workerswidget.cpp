#include "workerswidget.h"

#include "comboboxitemdelegate.h"

#include <QLabel>

WorkersWidget::WorkersWidget(SQLWorker *w)
{
    worker = w;

    setupWorker();
    setupUi();
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

}

void WorkersWidget::loadPage() {

}
