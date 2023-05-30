#include "case.h"
#include <time.h>
Case::Case(QObject *parent) : QObject(parent)
{
srand(time(0));
int a =5;
//while (a <= 8 or a >= 11)
//    a = rand() % 12 + 6;
count_of_complete = a;
}
void Case::GenerateTime() {
    srand(time(0));
    time_to_take = rand() % 40 + 20;
}
void Case::GenerateMoney(){
    srand(time(0));
    money = QString::number((rand() % 40 + 10) * (rand() % 40 + 10) * (rand() % 20 + 10) * (rand() % 30 + 10)) + " руб";
}
void Case::GeneratePlace(){
    srand(time(0));
    place = PlacesArr[rand()%5] + QString::number(rand() % 20);

}
int Case::CaseNumber() {
    Number++;
    return Number;
}
