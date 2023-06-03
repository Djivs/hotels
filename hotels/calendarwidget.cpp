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

    connect(this, &QCalendarWidget::clicked, this, [this] (const QDate &date) {
        highlightRange(QTextCharFormat());
        if ((QGuiApplication::keyboardModifiers() & Qt::ShiftModifier) && (!fromDate.isNull())) {
            toDate = date;
            highlightRange(highlighterFormat);
        } else {
            fromDate = date;
            toDate = QDate();
        }
        emit rangeChanged();
    });
}

void CalendarWidget::highlightRange(QTextCharFormat format) {
    if ((!fromDate.isNull()) && (!toDate.isNull())) {
        auto d0 = std::min(fromDate, toDate);
        auto d1 = std::max(fromDate, toDate);

        while (d0 <= d1) {
            this->setDateTextFormat(d0, format);
            d0 = d0.addDays(1);

        }
    }
}

void CalendarWidget::setRange(QDate from, QDate to) {
    highlightRange(QTextCharFormat());
    fromDate = from;
    toDate = to;
    highlightRange(highlighterFormat);
}

QPair<QDate, QDate> CalendarWidget::getRange() const {
    if (fromDate.isNull() && !toDate.isNull()) {
        return {toDate, toDate};
    } else if (!fromDate.isNull() && toDate.isNull()) {
        return {fromDate, fromDate};
    } else {
        auto d0 = std::min(fromDate, toDate);
        auto d1 = std::max(fromDate, toDate);
        return {d0, d1};
    }
}

QDate CalendarWidget::getFromDate() const {
    if (!toDate.isNull() && fromDate.isNull()) {
        return toDate;
    }

    return fromDate;
}
QDate CalendarWidget::getToDate() const {
    if (!fromDate.isNull() && toDate.isNull()) {
        return fromDate;
    }

    return toDate;
}
