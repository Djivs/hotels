#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QCalendarWidget>
#include <QObject>
#include <QWidget>
#include <QDate>
#include <QTextCharFormat>

class CalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    CalendarWidget();

    void setRange(QDate from, QDate to);


    QPair<QDate, QDate> getRange() const;
    QDate getFromDate() const;
    QDate getToDate() const;
signals:
    void rangeChanged();
private:
    void highlightRange(QTextCharFormat format);
    QDate fromDate;
    QDate toDate;

    QTextCharFormat highlighterFormat;



};

#endif // CALENDARWIDGET_H
