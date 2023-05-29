#ifndef PAYDAY_H
#define PAYDAY_H

#include <QObject>
#include "mainwindow.h"
class Payday : public QObject
{
    Q_OBJECT
public:
    explicit Payday(QObject *parent = nullptr);
    int workhours;
    void Worktime();
signals:

};

#endif // PAYDAY_H
