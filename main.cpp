#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCalendarWidget>
#include <QDateTime>
#include <QTimer>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setStyleSheet("background-color: #8B0000; color: white; font-family: 'monospace';");

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    QHBoxLayout *headerLayout = new QHBoxLayout();

    // Month/Year Label
    QLabel *dateLabel = new QLabel(QDate::currentDate().toString("MMMM yyyy"));
    
    // Digital Clock Label
    QLabel *clockLabel = new QLabel(QTime::currentTime().toString("hh:mm:ss"));
    
    // Timer to update clock every second
    QTimer *timer = new QTimer(&window);

    QObject::connect(timer, &QTimer::timeout, [=]() {
        clockLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
    });

    timer->start(1000);

    headerLayout->addWidget(dateLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(clockLabel);

    // Calendar
    QCalendarWidget *calendar = new QCalendarWidget();
    calendar->setNavigationBarVisible(false);

    calendar->setSelectionMode(QCalendarWidget::NoSelection);
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
        "border: 1px solid white;"
        "}"  
    );

    calendar->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);


    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(calendar);

    window.resize(1024, 600);
    window.show();
    return app.exec();
}