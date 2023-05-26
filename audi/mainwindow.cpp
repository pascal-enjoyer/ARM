#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "case.h"
#include "tempquastion1.h"
#include <QMessageBox>
Case c;


void MainWindow::RefreshTime() {
    QTextStream out(stdout);
    ui->time_label->setText("сейчас " + QTime::currentTime().toString(Qt::SystemLocaleShortDate));
    ui->date_label->setText("сегодня " + QDate::currentDate().toString(Qt::SystemLocaleShortDate));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->CasegroupBox->hide();
    ui->CaseGlData->hide();
    ui->CaseGlTime->hide();

    tmr = new QTimer();
    tmr->setInterval(30000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

    tmr2 = new QTimer();
    tmr2->setInterval(1000);
    connect(tmr2, SIGNAL(timeout()), this, SLOT(updateGlTime()));

    RefreshTime();

    ui->CountOfCompleteLabel->hide();
    ui->pushButton_2->hide();
    c.GenerateMoney();
    c.GenerateTime();
    c.GeneratePlace();
    ui->CaseNumber->setText("Заказ №" + QString::number(c.CaseNumber()));
    ui->TimeLabelDyn->setText(c.money);
    ui->MoneyLabelDyn->setText(c.time_to_take);
    ui->PlaceLabelDyn->setText(c.place);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime() {
    ui->time_label->setText("сейчас " + QTime::currentTime().toString(Qt::SystemLocaleShortDate));
}
void MainWindow::updateGlTime() {
    ui->CaseGlTime->setText(QTime::currentTime().toString(Qt::SystemLocaleShortDate));
    ui->CaseGlData->setText(QDate::currentDate().toString(Qt::SystemLocaleShortDate));
}
void MainWindow::on_pushButton_clicked()
{
    ui->CasegroupBox->show();

    ui->pushButton->hide();
    ui->pushButton_2->show();
    ui->time_label->hide();
    ui->date_label->hide();
    ui->CaseGlTime->setText( QTime::currentTime().toString(Qt::SystemLocaleShortDate));
    ui->CaseGlData->setText(QDate::currentDate().toString(Qt::SystemLocaleShortDate));

    ui->CaseGlData->show();
    ui->CaseGlTime->show();
    delete tmr;
    tmr2->start();
    QMessageBox::information(this, "Это окно можно закрыть", "Вы начали работать в " + QTime::currentTime().toString(Qt::SystemLocaleShortDate) + ", " + QDate::currentDate().toString(Qt::SystemLocaleShortDate));
    ui->CountOfCompleteLabel->show();

}

void MainWindow::on_pushButton_2_clicked()
{
    TempQuastion1 b;
    b.setModal(true);
    b.exec();
    if (b.yes == 1) {
        c.GenerateMoney();
        c.GeneratePlace();
        c.GenerateTime();
        ui->CaseNumber->setText("Заказ №" + QString::number(c.CaseNumber()));
        ui->TimeLabelDyn->setText(c.money);
        ui->MoneyLabelDyn->setText(c.time_to_take);
        ui->PlaceLabelDyn->setText(c.place);
        c.count_of_complete += 1;
        ui->CountOfCompleteLabel->setText(QString::number(c.count_of_complete));
    }
}

