#include "case.h"
#include <time.h>

Case::Case(QObject *parent) : QObject(parent)
{
srand(time(0));
}
void Case::GenerateTime() {
    srand(time(0));
    time_to_take = QString::number(rand() % 40 + 20) + " минут";
}
void Case::GenerateMoney(){
    srand(time(0));
    money = QString::number((rand() % 40 + 10) * (rand() % 40 + 10) * (rand() % 20 + 10) * (rand() % 30 + 10)) + " руб";
}
void Case::GeneratePlace(){
        srand(time(0));
    place = PlacesArr[rand()%5];
}
int Case::CaseNumber() {
    Number++;
    return Number;
}
