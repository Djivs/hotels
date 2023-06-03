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
    QDate getFromDate() const {return fromDate;}
    QDate getToDate() const {return toDate;}
private:
    void highlightRange(QTextCharFormat format);
    QDate fromDate;
    QDate toDate;

    QTextCharFormat highlighterFormat;



};

#endif // CALENDARWIDGET_H
