#include "login.h"
#include "ui_login.h"
#include "./begin.h"
#include <QApplication>
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{

    ui->setupUi(this);
//    qDebug()<<"访问ui.h内的控件"<<ui->loginlogin_Button->text();
    // 初始化声明的指针
    beginGame = new begin();
    registerWid = new registerWidget();
    // 链接槽
    // 开始游戏 -> 登录
    connect(beginGame,&begin::backToLogin,this,[=](){
        this->show();
        beginGame->hide();
    });
    // 注册 (返回)-> 登录
    connect(registerWid,&registerWidget::backToLogin,this,[=](){
        this->show();
        registerWid->hide();
    });
    // 注册 -> 登录
    connect(registerWid,&registerWidget::registed_and_Login,this,[=](){
        beginGame->show();
    });
    // 设置窗口title
    this->setWindowTitle("登录");
    beginGame->setWindowTitle("开始游戏");

}

login::~login()
{
    delete beginGame;
    delete registerWid;
    delete ui;
}



void login::on_loginlogin_Button_clicked()
{
    beginGame->show();
    this->hide();
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

