#ifndef TEMPQUASTION1_H
#define TEMPQUASTION1_H

#include <QDialog>

namespace Ui {
class TempQuastion1;
}

class TempQuastion1 : public QDialog
{
    Q_OBJECT

public:
    explicit TempQuastion1(QWidget *parent = nullptr);
    ~TempQuastion1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::TempQuastion1 *ui;
};

#endif // TEMPQUASTION1_H
