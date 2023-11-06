#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "./begin.h"
#include "./registerwidget.h"
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:

    void on_loginlogin_Button_clicked();


    void on_login_existPrograme_Button_clicked();

    void on_login_register_Button_clicked();

private:
    Ui::login *ui;
    begin *beginGame;
    registerWidget *registerWid;
};

#endif // LOGIN_H
