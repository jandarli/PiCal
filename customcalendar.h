#ifndef CUSTOMCALENDAR_H
#define CUSTOMCALENDAR_H

#include <QCalendarWidget>

class CustomCalendar : public QCalendarWidget
{
    Q_OBJECT
    public:
        explicit CustomCalendar(QWidget *parent = nullptr);
        void setWavePhase(double phase);

    protected:
        void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;

    private:
        double m_wavePhase = 0.0;
};

#endif