#include "tempquastion1.h"
#include "ui_tempquastion1.h"
#include "case.h"
#include <QMessageBox>
#include <QApplication>
QString a;
TempQuastion1::TempQuastion1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TempQuastion1)
{

    ui->setupUi(this);
    ui->stackedWidget2->setCurrentIndex(0);
    this->setWindowTitle("Окно поддержки");
}

TempQuastion1::~TempQuastion1()
{
    delete ui;
}

void TempQuastion1::on_pushButton_clicked()
{
    ui->stackedWidget2->setCurrentIndex(2);
}


void TempQuastion1::on_pushButton_2_clicked()
{
    ui->stackedWidget2->setCurrentIndex(1);
}

void TempQuastion1::on_No1pushButton_2_clicked()
{
    QMessageBox::information(this, "Это окно можно закрыть", "Можете продолжать работать");
    yes = 1;
    close();
}


void TempQuastion1::on_SendOtherpushButton_4_clicked()
{
    QMessageBox::information(this, "Это окно можно закрыть", "Сообщение о проблеме отправлено, можете продолжать работать");
    yes=1;
    close();
}


void TempQuastion1::on_SendCheckspushButton_3_clicked()
{
    a = "";
    if (ui->CarcheckBox->isChecked())
        a+="Механики вызваны.\n";
    if (ui->NotMoneycheckBox_2->isChecked())
        a+="Сообщение о недостатке денег отправлено.\n";
    if (ui->bankomatcheckBox_4->isChecked())
        a+="Сервис-инженеры по обслуживанию банкоматов\nвызваны.";
    if (ui->CaputcheckBox_3->isChecked())
        a+="Ответственные за маршрут\nсотрудники будут опевещены.\n";
    ui->label_2->setText(a + "При возможности продолжайте работать.");
    ui->stackedWidget2->setCurrentIndex(3);
}


void TempQuastion1::on_pushButton_3_clicked()
{
    yes = 1;
}

