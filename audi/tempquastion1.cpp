#include "tempquastion1.h"
#include "ui_tempquastion1.h"
#include "case.h"
TempQuastion1::TempQuastion1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TempQuastion1)
{

    ui->setupUi(this);
    ui->label_2->hide();
    ui->pushButton_3->hide();
}

TempQuastion1::~TempQuastion1()
{
    delete ui;
}

void TempQuastion1::on_pushButton_clicked()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->label->setText("Позвоните по номеру и \nсообщите о проблеме: 88005553535");
    ui->label_2->show();
    ui->pushButton_3->show();
}


void TempQuastion1::on_pushButton_2_clicked()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->label->hide();
    ui->label_2->show();
    ui->pushButton_3->show();
}

void TempQuastion1::on_pushButton_3_clicked()
{
    close();
}

