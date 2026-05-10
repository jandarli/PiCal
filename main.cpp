#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCalendarWidget>
#include <QDateTime>
#include <QTimer>
#include <QPushButton>
#include <QTextCharFormat>
#include <QPainter>

#include "customcalendar.h"
#include "pspwaves.h"


// Create widget class
class PicalWindow : public QWidget {
public:
    double wavePhase = 0.0;
    explicit PicalWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_OpaquePaintEvent);
    }
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        drawPSPWaves(&painter, rect(), rect(), wavePhase);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PicalWindow window;
    window.setStyleSheet("color: white; font-family: 'monospace'; font-size: 22px;");

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    QHBoxLayout *headerLayout = new QHBoxLayout();

    // Month/Year Label
    QLabel *dateLabel = new QLabel(QDate::currentDate().toString("MMMM yyyy"));
    
    // Digital Clock Label
    QLabel *clockLabel = new QLabel(QTime::currentTime().toString("hh:mm:ss"));
    
    // Current Month/Day Label
    QLabel *monthDayLabel = new QLabel(QDate::currentDate().toString("M/d"));
    monthDayLabel->setStyleSheet("font-weight: bold; margin-right: 10px;");

    // Timer to update clock every second
    QTimer *timer = new QTimer(&window);

    QObject::connect(timer, &QTimer::timeout, [=]() {
        clockLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
    });

    timer->start(1000);

    headerLayout->addWidget(dateLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(clockLabel);
    headerLayout->addWidget(monthDayLabel);


    // Calendar
    CustomCalendar *calendar = new CustomCalendar();

    QTextCharFormat whiteFormat;
    whiteFormat.setForeground(Qt::white);
    calendar->setWeekdayTextFormat(Qt::Saturday, whiteFormat);
    calendar->setWeekdayTextFormat(Qt::Sunday, whiteFormat);

    QPushButton *prevBtn = new QPushButton("◀");
    QPushButton *nextBtn = new QPushButton("▶");

    QString arrowStyle = 
        "QPushButton {"
        "   background: transparent;"
        "   border: none;"
        "   padding: 0px;"
        "   margin: 0px;"
        "   color: white;"
        "   font-size: 32px;"
        "   padding-bottom: 8px;"
        "}";

    prevBtn->setStyleSheet(arrowStyle);
    nextBtn->setStyleSheet(arrowStyle);

    prevBtn->setFixedWidth(30);
    nextBtn->setFixedWidth(30);

    QObject::connect(prevBtn, &QPushButton::clicked, calendar, &CustomCalendar::showPreviousMonth);
    QObject::connect(nextBtn, &QPushButton::clicked, calendar, &CustomCalendar::showNextMonth);

    headerLayout->insertWidget(0, prevBtn);
    headerLayout->insertWidget(2, nextBtn);

    QObject::connect(calendar, &CustomCalendar::currentPageChanged, [=](int year, int month) {
        QDate newDate(year, month, 1);
        dateLabel->setText(newDate.toString("MMMM yyyy"));
    });

    calendar->setNavigationBarVisible(false);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    calendar->setGridVisible(true);
    calendar->setStyleSheet(
        "QCalendarWidget QTableView {"
        "background-color: #8B0000;"
        "alternate-background-color: #8B0000;" 
        "selection-background-color: #00FF00;" 
        "}"
        
        "QCalendarWidget QHeaderView,"
        "QCalendarWidget QHeaderView::section,"
        "QCalendarWidget QWidget#qt_calendar_navigationbar {"
        "background-color: #8B0000;" 
        "color: white;"
        "border: 1px solid white;"
        "}"

        "QCalendarWidget QAbstractItemView {"
        "gridline-color: white;"
        "border-top: 1px solid white;"
        "border-left: 1px solid white;"
        "border-right: 0px;"
        "border-bottom: 0px;"
        "}"  
    );

    calendar->setHorizontalHeaderFormat(QCalendarWidget::LongDayNames);

    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(calendar);

    window.resize(1024, 600);
    window.show();
    return app.exec();
}