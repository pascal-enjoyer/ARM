#include "mainwindow.h"
#include "auth.h"
#include <QApplication>
#include <QTimer>
#include "tempquastion1.h"
#include "case.h"
int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    Auth w;
    w.show();
    return a.exec();
}
