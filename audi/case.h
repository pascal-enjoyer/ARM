#ifndef CASE_H
#define CASE_H

#include <QObject>
#include <iostream>
#include <QString>
class Case : public QObject
{
    Q_OBJECT
public:
explicit Case(QObject *parent = nullptr);
int time_to_take;
QString money;
QString place;
bool count_of_loose = false;
int count_of_shtraf;
int count_of_complete;
int Number = 0;
void GenerateTime();
void GenerateMoney();
QString PlacesArr[5]{"Монетка", "Пятерочка", "сбер", "тинькофф", "альфабанк"};
void GeneratePlace();
int CaseNumber();
signals:

};

#endif // CASE_H
