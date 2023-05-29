#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "case.h"
#include "tempquastion1.h"
#include <QMessageBox>
#include <QFile>
#include "auth.h"
#include <QDir>
Case c;
int count_of_hours;
int count_of_hours_1case;
QFile written_requests2("C:/Qt/Qt5.12.12/audi/requests/written_requests.txt");
QFile requests2("C:/Qt/Qt5.12.12/audi/requests/requests.txt");
QFile userdata("C:/Qt/Qt5.12.12/audi/userdata/userdata.txt");
QFile file("C:/Qt/Qt5.12.12/audi/worktime/worktime.txt");

QString full_info_of_user;

int v = c.count_of_complete;
void MainWindow::RefreshTime() {
    QTextStream out(stdout);
    ui->time_label->setText("сейчас " + QTime::currentTime().toString(Qt::SystemLocaleShortDate));
    ui->date_label->setText("сегодня " + QDate::currentDate().toString(Qt::SystemLocaleShortDate));
}
QString formatMinutes(int minutes)
{
    int lastDigit = minutes % 10;
    int penultimateDigit = (minutes / 10) % 10;

    if (penultimateDigit == 1)
        return QString::number(minutes) + " минут.";

    if (lastDigit == 1)
        return QString::number(minutes) + " минута.";
    else if (lastDigit >= 2 && lastDigit <= 4)
        return QString::number(minutes) + " минуты.";
    else
        return QString::number(minutes) + " минут.";
}
QString formatOrders(int count)
{
    int lastDigit = count % 10;
    int penultimateDigit = (count / 10) % 10;

    if (penultimateDigit == 1)
        return QString::number(count) + " заказов.";

    if (lastDigit == 1)
        return QString::number(count) + " заказ.";
    else if (lastDigit >= 2 && lastDigit <= 4)
        return QString::number(count) + " заказа.";
    else
        return QString::number(count) + " заказов.";
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->other_requests_list->hide();


    this->setWindowTitle("Инкассатор-про");
    ui->menuBar->hide();
    ui->pushButton_2->setDisabled(true);
    ui->stackedWidget->setCurrentIndex(0);
    tmr = new QTimer(this);
    tmr->setInterval(30000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

    tmr2 = new QTimer(this);
    tmr2->setInterval(1000);
    connect(tmr2, SIGNAL(timeout()), this, SLOT(updateGlTime()));

    tmr3 = new QTimer(this);
    tmr3->setInterval(1000);
    connect(tmr3, SIGNAL(timeout()), this, SLOT(worktime()));
    connect(tmr3, SIGNAL(timeout()), this, SLOT(updateCaseTime()));

    RefreshTime();
    ui->CountOfCompleteLabel->setText(formatOrders(c.count_of_complete));
    c.GenerateMoney();
    c.GenerateTime();
    c.GeneratePlace();
    c.Number = 1;
    ui->CaseNumber1->setText(QString::number(c.Number));
    ui->TimeLabelDyn->setText(c.money);
    ui->MoneyLabelDyn->setText(formatMinutes(c.time_to_take));
    ui->PlaceLabelDyn->setText(c.place);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateCaseTime() {
    if (c.time_to_take == 0){
        if (c.count_of_loose == 1) {
            tmr3->stop();
            QMessageBox::warning(this, "Это окно можно закрыть", "На вас наложен штраф, можете приступать к новому заказу.");
            c.count_of_loose = 0;
        }
        else {
            tmr3->stop();
            QMessageBox::information(this, "Это окно можно закрыть", "У вас кончилось время, если опоздание\nне было обоснованным, то на вас будет наложен штраф.");
            c.count_of_loose++;
            c.time_to_take += 10;
            tmr3->start();
        }
    }
    else {
        c.time_to_take--;
        ui->MoneyLabelDyn->setText(formatMinutes(c.time_to_take));
    }
}
void MainWindow::worktime() {
    count_of_hours++;
    count_of_hours_1case++;
}
void MainWindow::updateTime() {
    ui->time_label->setText("сейчас " + QTime::currentTime().toString(Qt::SystemLocaleShortDate));
}
void MainWindow::updateGlTime() {
    ui->CaseGlTime->setText(QTime::currentTime().toString(Qt::SystemLocaleLongDate)+ " " + QDate::currentDate().toString(Qt::SystemLocaleShortDate));
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->CaseGlTime->setText(QTime::currentTime().toString(Qt::SystemLocaleLongDate)+ " " +QDate::currentDate().toString(Qt::SystemLocaleShortDate));
    delete tmr;
    tmr2->start();
    ui->CountOfCompleteLabel->show();
    ui->pushButton->setDisabled(true);
    ui->CaseStartButton->setEnabled(true);
    ui->menuBar->show();
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString dateTimeString = currentDateTime.toString(Qt::ISODate);
        out << Auth::UserLogon << " " << dateTimeString << endl;
        file.close();
    }
    QMessageBox::information(this, "Это окно можно закрыть", "Вы начали работать в " + QTime::currentTime().toString(Qt::SystemLocaleShortDate) + ", " + QDate::currentDate().toString(Qt::SystemLocaleShortDate));

}
QString getImagePathByLogin(const QString& login)
{
    QString imagePath;
    QDir imageDir("C:/Qt/Qt5.12.12/audi/profile_images");
    QStringList fileList = imageDir.entryList(QDir::Files);
    for (const QString& file : fileList) {
        QString fileName = file.section('.', 0, 0);
        if (fileName == login) {
            imagePath = imageDir.absoluteFilePath(file);
            break;
        }
    }

    return imagePath;
}

void MainWindow::on_pushButton_2_clicked()
{
    TempQuastion1 b;
    b.setModal(true);
    b.exec();
    if (b.yes == 1) {
        c.count_of_complete -= 1;
        if (c.count_of_complete == 0) {
            ui->stackedWidget->setCurrentIndex(2);
            ui->AllTimeEndLabel->setText("Вы выполнили все заказы.\nЗа " + formatMinutes(count_of_hours) + formatOrders(v));
        }
        else {
            tmr3->stop();
            c.GenerateMoney();
            c.GeneratePlace();
            c.GenerateTime();
            ui->case_list->addItem("№" + QString::number(c.Number) + " | " + c.money + ". | Выполнено за " + formatMinutes(count_of_hours_1case) + " | " + c.place + ".");
            count_of_hours_1case = 0;
            ui->CaseNumber1->setText(QString::number(c.CaseNumber()));
            ui->TimeLabelDyn->setText(c.money);
            ui->MoneyLabelDyn->setText(formatMinutes(c.time_to_take));
            ui->PlaceLabelDyn->setText(c.place);
            ui->CountOfCompleteLabel->setText(formatOrders(c.count_of_complete));
            ui->CaseStartButton->setEnabled(true);
            ui->pushButton_2->setDisabled(true);

        }
    }
}
void MainWindow::UserName() {
    if (!userdata.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл userdata.txt");
        return;
    }
    QTextStream in(&userdata);
    in.setCodec("UTF-8");
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(':');
        if (parts.size() == 3) {
            QString storedUsername = parts.at(0);
            if (Auth::UserLogon == storedUsername) {
                QString storedName = parts.at(1);
                QString storedAge = parts.at(2);
                userdata.close();
                full_info_of_user = QString(storedName) + " " + QString(storedAge) + " лет.";
                return;
            }
        }
    }
}

void MainWindow::on_CaseStartButton_clicked()
{

    tmr3->start();
    ui->CaseStartButton->setDisabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->label->setText("Осталось времени: ");
}


void MainWindow::on_EndDayButton_3_clicked()
{
    close();
    delete tmr2;
    delete tmr3;
}


void MainWindow::on_action_4_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_action_3_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->profile_image->setStyleSheet("border-radius:8px; border: 1px solid gray;background-image: url(" + getImagePathByLogin(Auth::UserLogon) + ")");
    UserName();
    ui->UserInfo->setText(full_info_of_user);
}


void MainWindow::on_action_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->requests_list->clear();
    ui->other_requests_list->clear();
    if (requests2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&requests2);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(":");
            if (parts.size() == 2)
            {
                QString login = parts[0];
                QString problems = parts[1];
                if (Auth::UserLogon == login) {
                    ui->requests_list->addItem(problems);
                }
            }
        }
        requests2.close();
    }
    if (written_requests2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&written_requests2);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(":");
            if (parts.size() == 2)
            {
                QString login = parts[0];
                QString problems = parts[1];
                if (Auth::UserLogon == login) {
                    ui->other_requests_list->addItem(problems);
                }
            }
        }
        written_requests2.close();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if (ui->other_requests_list->isHidden()) {
        ui->requests_list->hide();
        ui->other_requests_list->show();
    }
    else if (ui->requests_list->isHidden()) {
        ui->requests_list->show();
        ui->other_requests_list->hide();
    }
}

