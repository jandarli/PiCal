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
    
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(calendar);

    window.resize(1024, 600);
    window.show();
    return app.exec();
}