#include "formwidget.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QSizePolicy>
#include <QHeaderView>
#include <QDebug>

FormWidget::FormWidget(QWidget *parent)
    : QWidget{parent} {


}
void FormWidget::setupFormHeader() {
    formHeader = new FormHeader;

    connect(formHeader, &FormHeader::exit, this, [this] () {emit exit();});
    connect(formHeader, &FormHeader::prev, this, [this] () {
        if (curInd - 1) {
            --curInd;
            loadPage();
        }
    });
    connect(formHeader, &FormHeader::next, this, [this] () {
        ++curInd;
        loadPage();
    });
}

void FormWidget::printPage() {
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(QFileDialog::getSaveFileName());
    printer.setFullPage(true);

    QPainter painter(&printer);


    double xscale = printer.pageRect(QPrinter::DevicePixel).width() / double(this->width());
    double yscale = printer.pageRect(QPrinter::DevicePixel).height() / double(this->height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect(QPrinter::DevicePixel).center());
    painter.scale(scale, scale);
    painter.translate(-this->width()/ 2, -this->height()/ 2);

    this->render(&painter);
}

void FormWidget::resizeTableView(QTableView *v) {
    v->setMinimumSize(v->model()->columnCount() * TABLE_CELL_SIZE, (v->model()->rowCount() + 1) * TABLE_CELL_SIZE);
    v->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    v->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void FormWidget::showSearchError() {
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setText("Таких записей нет!");
    msg.setWindowTitle("Ошибка");
    msg.exec();
}

void FormWidget::showSaved() {
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    msg.setText("Сохранено!");
    msg.setWindowTitle("Сохранение");
    msg.exec();
}
