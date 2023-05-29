#ifndef TEMPQUASTION1_H
#define TEMPQUASTION1_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class TempQuastion1;
}

class TempQuastion1 : public QDialog
{
    Q_OBJECT

public:
    bool yes = 0;
    explicit TempQuastion1(QWidget *parent = nullptr);
    ~TempQuastion1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_No1pushButton_2_clicked();

    void on_SendOtherpushButton_4_clicked();

    void on_SendCheckspushButton_3_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::TempQuastion1 *ui;
};

#endif // TEMPQUASTION1_H
