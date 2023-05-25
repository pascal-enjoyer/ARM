#include "mainwindow.h"
#include "auth.h"
#include <QApplication>
#include <QTimer>
#include "case.h"
int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QTimer::singleShot(5000, &w, SLOT(updateTime()));
    return a.exec();
}
