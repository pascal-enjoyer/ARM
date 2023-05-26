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

    ui->checkgroupBox_2->hide();
    ui->textEdit->hide();
    ui->SendOtherpushButton_4->hide();
    ui->label->hide();
    ui->groupBox_3->hide();
}

TempQuastion1::~TempQuastion1()
{
    delete ui;
}

void TempQuastion1::on_pushButton_clicked()
{

}


void TempQuastion1::on_pushButton_2_clicked()
{

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
    if (ui->CarcheckBox->isChecked())
        a+="Механики вызваны.\n";
    if (ui->NotMoneycheckBox_2->isChecked())
        a+="Сообщение о недостатке денег отправлено.\n";
    if (ui->bankomatcheckBox_4->isChecked())
        a+="Сервис-инженеры по обслуживанию банкоматов\nвызваны.";
    if (ui->CaputcheckBox_3->isChecked())
        a+="Ответственные за маршрут\nсотрудники будут опевещены.\nПри возможности продолжайте работать.";
    ui->label_2->setText(a);
    ui->groupBox->hide();
    ui->groupBox_3->show();
    ui->pushButton->hide();
}


void TempQuastion1::on_pushButton_3_clicked()
{
    yes = 1;
}

