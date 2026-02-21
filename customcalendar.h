#ifndef CUSTOMCALENDAR_H
#define CUSTOMCALENDAR_H

#include <QCalendarWidget>

class CustomCalendar : public QCalendarWidget
{
    Q_OBJECT
    public:
        explicit CustomCalendar(QWidget *parent = nullptr);

    protected:
        void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;
};

#endif