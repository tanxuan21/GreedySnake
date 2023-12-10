#include "registerwidget.h"
#include "ui_registerwidget.h"
#include <QRegularExpression>
#include "../dataHandler/userdata.h"
registerWidget::registerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
}

registerWidget::~registerWidget()
{
    delete ui;
}

void registerWidget::on_register_back_Button_clicked()
{
    emit backToLogin();
    this->hide();
}


void registerWidget::on_register_confirm_Button_clicked()
{
    QString username = ui->username_lineEdit->text();// 用户名.检测是否合法.
    QString password = ui->password_lineEdit->text();// 密码.检测是否合法.
    if(username == "" || password == ""){
        ui->info->setText("用户名或者密码不能为空");
        return;
    }
    static QRegularExpression reg("[^(a-zA-Z0-9_)]"); // 创建正则表达式,来判读用户名和密码是否合法.
    QRegularExpressionMatch matchUser = reg.match(username);
    qDebug()<<"匹配"<<matchUser.hasMatch();
    QRegularExpressionMatch matchPassword = reg.match(password);

    if((!(matchUser.hasMatch()))&&(!(matchPassword.hasMatch()))){
        userData *user = new userData(username,password);// 创建对象.
        if(user->writeInDataBase()){// 写入.
            ui->username_lineEdit->setText("");
            ui->password_lineEdit->setText("");
            ui->info->setText("");
            emit registed_and_Login(user);
            // 确认注册
            this->hide();
        }
        else{
            ui->info->setText("用户已存在,请登录");
        }

    }
    else{
        ui->info->setText("用户名或者密码不合法.只允许字母,数字,下划线.");
    }

}

