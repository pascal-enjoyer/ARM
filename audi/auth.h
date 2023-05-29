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
    explicit Auth(QWidget *parent = nullptr);
    ~Auth();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Auth *ui;
};

#endif // AUTH_H
