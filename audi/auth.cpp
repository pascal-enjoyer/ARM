#include "auth.h"
#include "ui_auth.h"
#include "mainwindow.h"
#include <QFile>
#include <QMessageBox>
QFile AuthFile("C:/Qt/Qt5.12.12/audi/auth/auth.txt");

Auth::Auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auth)
{
    ui->setupUi(this);
    this->setWindowTitle("Окно авторизации");
}

Auth::~Auth()
{
    delete ui;

}
QString Auth::UserLogon;
void Auth::on_pushButton_clicked()
{
    if (!AuthFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл auth.txt");
        return;
    }

    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    QTextStream in(&AuthFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(':');
        if (parts.size() == 2) {
            QString storedUsername = parts.at(0);
            QString storedPassword = parts.at(1);
            if (username == storedUsername && password == storedPassword) {
                Auth::UserLogon = username;
                AuthFile.close();
                close();
                MainWindow* w = new MainWindow();
                w->setAttribute(Qt::WA_DeleteOnClose);
                w->show();
                return;
            }
        }
    }

    AuthFile.close();
    ui->label_3->setText("Неверный логин или пароль");
}

