#include "startgame.h"
#include "begin.h"
#include <QScrollArea>
startGame::startGame(QWidget *parent)
    : QWidget{parent}
{
    // 下一个界面
    this->game = new Game();

    // 这个界面
    this->beginwidget = new begin(this);
    this->setting = new Setting();

    this->scrollWidget = new QScrollArea(this);
    scrollWidget->setWidget(setting);
    scrollWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 几何数据
    scrollWidget->hide();
    this->setMaximumWidth(800);
    this->setMaximumHeight(700);
    this->setMinimumWidth(520);
    this->setMinimumHeight(400);
    // 链接游戏界面的显示
    connect(game,&Game::backToBegin,this,[=](){
        this->show();
        game->hide();
    });
    // 回到登录界面
    connect(beginwidget,&begin::backToLogin,this,[=](){
        this->hide();
        emit backToLogin();
    });


    // 开始新游戏
    connect(beginwidget,&begin::newGame,this,[=](){
        this->hide();
        game->show();
    });


    beginwidget->resize(this->width(),this->height());
    // 开始游戏界面 到 设置界面
    connect(beginwidget,&begin::toSetting,this,[=](){
        beginwidget->hide();
        scrollWidget->show();
    });
    // 设置界面 返回 开始游戏界面
    connect(setting,&Setting::toStartGame,this,[=](){
        beginwidget->show();
        scrollWidget->hide();
    });


}

startGame::~startGame(){
        delete game;

}


void startGame::resizeEvent(QResizeEvent *)
{
//    setting->resize(this->width(),this->height());
    beginwidget->resize(this->width(),this->height());
    scrollWidget->resize(this->width(),this->height());
    setting->resize(this->width(),this->height());
    if(this->height()>680){
        scrollWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    else{
        scrollWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }
}

void startGame::on_begin_loginOut_button_clicked()
{
    emit backToLogin();
}


void startGame::on_begin_startNewGame_Button_clicked()
{
    game->show();
    this->hide();
}

