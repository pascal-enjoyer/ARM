#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QTime>
#include <QTimer>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void CaseUpdate();
    void RefreshTime();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void updateTime();
    void updateGlTime();
    void updateCaseTime();
    void worktime();
    void on_pushButton_2_clicked();
    void UserName();
    void on_CaseStartButton_clicked();

    void on_EndDayButton_3_clicked();

    void on_action_4_triggered();

    void on_action_3_triggered();

    void on_action_triggered();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    QTimer *tmr2;
    QTimer *tmr3;

};
#endif // MAINWINDOW_H
