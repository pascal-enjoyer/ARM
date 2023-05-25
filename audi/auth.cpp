#include "auth.h"
#include "ui_auth.h"
#include "mainwindow.h"

Auth::Auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auth)
{
    ui->setupUi(this);
}

Auth::~Auth()
{
    delete ui;
}

void Auth::on_pushButton_clicked()
{
//    close();
//    MainWindow* w = new MainWindow();
//    w->setAttribute(Qt::WA_DeleteOnClose);
//    w->show();
    if (ui->lineEdit->text() == "admin" and ui->lineEdit_2->text() == "admin") {
        close();
        MainWindow* w = new MainWindow();
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
    }
    else {
        ui->label_3->setText("Неверный логин или пароль");
    }
}

