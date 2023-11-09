#include "startgame.h"
#include "begin.h"
#include <QScrollArea>
#include "./picksave.h"
startGame::startGame(QWidget *parent)
    : QWidget{parent}
{
/*
界面初始化
*/

    // 游戏界面
    this->game = new Game();

    // 开始游戏界面
    this->beginwidget = new begin(this);
    // 设置界面
    //     设置界面放在滚动区里.
    this->scrollWidget = new QScrollArea(this);
    this->setting = new Setting();
    scrollWidget->setWidget(setting);
    scrollWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollWidget->hide();
    // 选取存档界面
    this->pickSaveWidget = new pickSave(this);
    this->pickSaveWidget->hide();
/*
界面几何数据
*/
    // 几何数据
    this->setMaximumWidth(800);
    this->setMaximumHeight(700);
    this->setMinimumWidth(520);
    this->setMinimumHeight(400);
    this->beginwidget->resize(this->width(),this->height());
    this->pickSaveWidget->resize(this->width(),this->height());
/*
绑定界面跳转按钮事件
*/
    // 游戏界面 -> 开始游戏界面
    connect(game,&Game::backToBegin,this,[=](){
        this->show();
        this->game->hide();
    });

    // 开始游戏界面-> 登录界面
    connect(beginwidget,&begin::backToLogin,this,[=](){
        this->hide();
        emit backToLogin();
    });

    // 开始游戏界面 -> 新游戏
    connect(beginwidget,&begin::newGame,this,[=](){
        this->hide();
        this->game->show();
    });

    // 开始游戏界面 -> 设置界面
    connect(beginwidget,&begin::toSetting,this,[=](){
        this->beginwidget->hide();
        this->scrollWidget->show();
    });
    // 设置界面 -> 开始游戏界面
    connect(setting,&Setting::toStartGame,this,[=](){
        this->beginwidget->show();
        this->scrollWidget->hide();
    });
    // 开始游戏界面 -> 存档列表界面
    connect(beginwidget,&begin::startFromSave,this,[=](){
        this->beginwidget->hide();
        this->pickSaveWidget->show();
    });
    // 存档列表界面 -> 开始游戏界面
    connect(pickSaveWidget,&pickSave::backToBegin,this,[=](){
        this->beginwidget->show();
        this->pickSaveWidget->hide();
    });
}

startGame::~startGame(){
        delete game;
}

// resize事件
void startGame::resizeEvent(QResizeEvent *)
{
    // 所有子对象跟随resize.
    this->beginwidget->resize(this->width(),this->height());
    this->scrollWidget->resize(this->width(),this->height());
    this->pickSaveWidget->resize(this->width(),this->height());
    this->setting->resize(this->width(),this->height());
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

