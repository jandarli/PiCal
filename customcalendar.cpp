#include "customcalendar.h"
#include "pspwaves.h"
#include <QPainter>

CustomCalendar::CustomCalendar(QWidget *parent) : QCalendarWidget(parent) {}

void CustomCalendar::setWavePhase(double phase)
{
    m_wavePhase = phase;
    update();
}

void CustomCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    painter->save();

    drawPSPWaves(painter, rect, this->rect(), m_wavePhase);

    if (date == selectedDate()) {
        painter->fillRect(rect, QColor("#00FF00"));
    }

    if (date.month() == monthShown()) {
        painter->setPen(Qt::white);
        QRect textRect = rect.adjusted(6, 4, -4, -4);
        painter->drawText(textRect, Qt::AlignTop | Qt::AlignLeft, QString::number(date.day()));
    }

    painter->restore();
}