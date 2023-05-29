#ifndef AUTH_H
#define AUTH_H

#include <QDialog>
#include <QString>

namespace Ui {
class Auth;

}

class Auth : public QDialog
{
    Q_OBJECT

public:
    static QString UserLogon;

    QString loginPassword[10]{"admin", "00000", "alexey", "11111", "david", "22222", "vlad", "33333", "kirill", "44444"};
    explicit Auth(QWidget *parent = nullptr);
    ~Auth();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Auth *ui;
};

#endif // AUTH_H
