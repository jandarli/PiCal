#include "customcalendar.h"
#include <QPainter>

CustomCalendar::CustomCalendar(QWidget *parent): QCalendarWidget(parent){ }

void CustomCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    painter->save();

    if (date == selectedDate()) {
        painter->fillRect(rect, QColor("#00FF00"));
    } else {
        painter->fillRect(rect, QColor("#8B0000"));
    }

    painter->setPen(Qt::white);

    QRect textRect = rect.adjusted(6, 4, -4, -4);
    painter->drawText(textRect, Qt::AlignTop | Qt::AlignLeft, QString::number(date.day()));
    painter->restore();
}