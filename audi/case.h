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
QString time_to_take;
QString money;
QString place;
int count_of_complete;
int Number = 0;
void GenerateTime();
void GenerateMoney();
QString PlacesArr[5]{"Монетка1", "Пятерочка2", "сбер2", "тинькофф21", "альфабанк4"};
void GeneratePlace();
int CaseNumber();
signals:

};

#endif // CASE_H
