#include "calendarwidget.h"

#include <QPalette>
#include <QApplication>
#include <QGuiApplication>
#include <QCoreApplication>
#include <QDebug>
#include <algorithm>


CalendarWidget::CalendarWidget() {
    highlighterFormat.setBackground(this->palette().brush(QPalette::Highlight));
    highlighterFormat.setForeground(this->palette().color(QPalette::HighlightedText));

    qDebug() << dateTextFormat();

    connect(this, &QCalendarWidget::clicked, this, [this] (const QDate &date) {
        highlightRange(QTextCharFormat());
        if ((QGuiApplication::keyboardModifiers() & Qt::ShiftModifier) && (!fromDate.isNull())) {
            toDate = date;
            highlightRange(highlighterFormat);
        } else {
            fromDate = date;
            toDate = QDate();
        }
    });
}

void CalendarWidget::highlightRange(QTextCharFormat format) {
    if ((!fromDate.isNull()) && (!toDate.isNull())) {
        auto d0 = std::min(fromDate, toDate);
        auto d1 = std::max(fromDate, toDate);

        while (d0 <= d1) {
            qDebug() << toDate << fromDate;
            this->setDateTextFormat(d0, format);
            d0 = d0.addDays(1);

        }
    }
}
