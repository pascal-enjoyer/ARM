#include "tempquastion1.h"
#include "ui_tempquastion1.h"
#include "case.h"
#include <QMessageBox>
#include <QApplication>
#include "auth.h"
QString a;
QFile requests("C:/Qt/Qt5.12.12/audi/requests/requests.txt");
QFile written_requests("C:/Qt/Qt5.12.12/audi/requests/written_requests.txt");
TempQuastion1::TempQuastion1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TempQuastion1)
{

    ui->setupUi(this);
    ui->stackedWidget2->setCurrentIndex(0);
    this->setWindowTitle("У вас были проблемы?");
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
    QString b = ui->textEdit->toPlainText();
    if (b.isEmpty() or b.count(' ') == b.length()) {
        QMessageBox::information(this, "Вы ничего не написали", "Опишите вашу проблему или вернитесь назад.");
        return;
    }
    if (written_requests.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&written_requests);
        out << Auth::UserLogon << ":" << b << "\n";
        written_requests.close();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи");
    }
    QMessageBox::information(this, "Это окно можно закрыть", "Сообщение о проблеме отправлено, можете продолжать работать");
    yes=1;
    close();
}


void TempQuastion1::on_SendCheckspushButton_3_clicked()
{
    a = "";
    QString b = "";
    if (ui->CarcheckBox->checkState() == (Qt::Unchecked) and ui->NotMoneycheckBox_2->checkState() == (Qt::Unchecked) and ui->bankomatcheckBox_4->checkState() == (Qt::Unchecked) and ui->CaputcheckBox_3->checkState() == (Qt::Unchecked)) {
        QMessageBox::information(this, "Вы ничего не выбрали", "Выберите пункты или вернитесь назад.");
        return;
    }
    if (ui->CarcheckBox->isChecked()){
        a+="Механики вызваны.\n";
        b+="Неисправность транспорта. ";
    }
    if (ui->NotMoneycheckBox_2->isChecked()) {
        a+="Сообщение о недостатке денег отправлено.\n";
        b+="Полученны не все деньги. ";
    }
    if (ui->bankomatcheckBox_4->isChecked()) {
        a+="Сервис-инженеры по обслуживанию банкоматов\nвызваны.";
        b+="Неисправность банкомата. ";
    }

    if (ui->CaputcheckBox_3->isChecked()) {
        a+="Ответственные за маршрут\nсотрудники будут опевещены.\n";
        b+="Изменение маршрута.";
    }
    ui->label_2->setText(a + "При возможности продолжайте работать.");
    ui->stackedWidget2->setCurrentIndex(3);
    if (requests.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&requests);
        out << Auth::UserLogon << ":" << b << "\n";
        requests.close();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи");
    }
}


void TempQuastion1::on_pushButton_3_clicked()
{
    yes = 1;
}


void TempQuastion1::on_pushButton_4_clicked()
{
    ui->stackedWidget2->setCurrentIndex(1);
}


void TempQuastion1::on_pushButton_6_clicked()
{
    close();
}


void TempQuastion1::on_pushButton_5_clicked()
{
    ui->stackedWidget2->setCurrentIndex(0);
}

