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
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    QTimer *tmr2;
};
#endif // MAINWINDOW_H
