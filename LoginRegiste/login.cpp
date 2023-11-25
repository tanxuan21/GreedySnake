#include "login.h"
#include "ui_login.h"
#include "./ReadyToPlay/startgame.h"
#include <QApplication>
#include "../dataHandler/userdata.h"
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{

    ui->setupUi(this);
//    qDebug()<<"访问ui.h内的控件"<<ui->loginlogin_Button->text();
    // 初始化声明的指针
    start_game = new startGame();
    registerWid = new registerWidget();
    // 链接槽
    // 开始游戏 -> 登录
    connect(start_game,&startGame::backToLogin,this,[=](){
        this->show();
        start_game->hide();
    });
    // 注册 (返回)-> 登录
    connect(registerWid,&registerWidget::backToLogin,this,[=](){
        this->show();
        registerWid->hide();
    });
    // 注册 -> 登录
    connect(registerWid,&registerWidget::registed_and_Login,this,[=](userData user){
        start_game->setUser(user.getUsername());
        start_game->show();
    });
    // 设置窗口title
    this->setWindowTitle("登录");
    start_game->setWindowTitle("开始游戏");


    // 输入用户名密码时关闭提示信息
    connect(ui->username_lineEdit,&QLineEdit::textEdited,this,[=](){
          this->ui->info->setText("");
    });
    connect(ui->password_LineEdit,&QLineEdit::textEdited,this,[=](){
          this->ui->info->setText("");
    });

}

login::~login()
{
    delete start_game;
    delete registerWid;
    delete ui;
}



void login::on_loginlogin_Button_clicked()
{
    // .trimmed是删除首尾空格的方法.
    if(ui->username_lineEdit->text().trimmed() == ""){
        ui->info->setText("用户名密码不能为空");
    }
    else
    {
        // 如果找到了,就验证密码.
        userData *user = userData::findUser(ui->username_lineEdit->text().trimmed());
        if(user){
            if(user->getpassword() == ui->password_LineEdit->text()){

                ui->username_lineEdit->setText("");
                ui->password_LineEdit->setText("");
                start_game->show();
                start_game->setUser(user->getUsername());
                this->hide();
                // 注意要把信息去掉.

            }
            else{
                ui->info->setText("密码错误");
            }
        }
        // 找不到就卡住
        else{
            ui->info->setText("用户不存在,请注册");
        }
    }
}

void login::on_login_existPrograme_Button_clicked()
{
    QApplication::quit();
}


void login::on_login_register_Button_clicked()
{
    this->hide();
    registerWid->show();
}

