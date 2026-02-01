#include <QApplication>
#include <QCalendarWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QCalendarWidget calendar;
    calendar.setWindowTitle("Pi Dashboard");
    calendar.resize(1024, 600);
    calendar.show();

    return app.exec();
}