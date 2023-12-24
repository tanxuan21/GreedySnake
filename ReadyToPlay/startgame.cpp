#include "startgame.h"
#include "../game/recordplayer.h"
#include "begin.h"
#include <QScrollArea>
#include "./picksave.h"
#include "config.h"
#include <QDir>
#include <QFile>
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
    // 创建设置界面
    this->createSetting();

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
        this->game->setGameOption(-1,this->setting_data,Map::createMap(this->setting_data),nullptr);
    });

    // 开始游戏界面 -> 设置界面
    connect(beginwidget,&begin::toSetting,this,[=](){

        this->beginwidget->hide();
        this->scrollWidget->show();
    });
    // 设置界面 -> 返回
    connect(setting,&Setting::toStartGame,this,[=](){// Backmodel管理返回的界面是什么.
        if(settingBackmodel == 0){
            this->beginwidget->show();
        }
        else if(settingBackmodel == 1){
            this->pickSaveWidget->show();
            pickSaveWidget->readMap(this->user);
        }
        this->scrollWidget->close();
    });
    // 开始游戏界面 -> 存档列表界面
    connect(beginwidget,&begin::startFromSave,this,[=](){
        this->beginwidget->hide();
        this->pickSaveWidget->show();
        pickSaveWidget->readMap(this->user);
        settingBackmodel = 1;
    });
    // 存档列表界面 -> 开始游戏界面
    connect(pickSaveWidget,&pickSave::backToBegin,this,[=](){
        this->beginwidget->show();
        this->pickSaveWidget->hide();
        this->CurrentMapID = -1;
        // 原来的没用了.不要让存档里的设置影响到新游戏的设置.
        delete setting_data;
        this->setting_data = new settingData();
        this->setting->writeSettingDataToComponent(this->setting_data);
        settingBackmodel = 0;
    });
    // 存档列表界面 -> *
    // 继续游戏
    connect(pickSaveWidget,&pickSave::continuePaly,this,[=](int MapId){
        this->CurrentMapID = MapId;
        if(map != 0){
            delete map;

        }
        if(record != 0){
            delete record;
        }

        map = user->readMap(QString(projectPath)+"data/game/"+this->user->getUsername()+"/"+QString::number(MapId)+"/"+user->getUsername()+".map");
        record = user->readrecord(QString(projectPath)+"data/game/"+this->user->getUsername()+"/"+QString::number(MapId)+"/"+user->getUsername()+".rec");
        setting_data = Setting::readSettingDataFromFolder(this->user->getPath()+QString::number(MapId)+"/"+user->getUsername()+".config");
        this->setting->writeSettingDataToComponent(setting_data);
        this->game->setGameOption(MapId,setting_data,map,record);
        this->game->show();
        this->hide();
    });
    // 回放
    connect(pickSaveWidget,&pickSave::review,this,[=](int MapId){
        qDebug()<<MapId<<"回放";
        this->CurrentMapID = MapId;
        if(map != 0){
            delete map;

        }
        if(record != 0){
            delete record;
        }
        map = user->readMap(QString(projectPath)+"data/game/"+this->user->getUsername()+"/"+QString::number(MapId)+"/"+user->getUsername()+".map");
        //record = user->readrecord(QString(projectPath)+"data/game/"+this->user->getUsername()+"/"+QString::number(MapId)+"/"+user->getUsername()+".rec");
        record = Record::readrecord(QString(projectPath)+"data/game/"+this->user->getUsername()+"/"+QString::number(MapId)+"/"+user->getUsername()+".rec");

        setting_data = Setting::readSettingDataFromFolder(this->user->getPath()+QString::number(MapId)+"/"+user->getUsername()+".config");
        this->setting->writeSettingDataToComponent(setting_data);
//        this->game->setGameOption(MapId,setting_data,map,record);
//        this->game->show();
        player = new recordPlayer();
        this->player->setGameOption(MapId,setting_data,map,record);
//        Record::debug(record);
        player->show();
        // 回放界面到开始游戏界面
        connect(player,&recordPlayer::rec_backToBegin,this,[=](){
            qDebug()<<"父窗口接受函数";
            this->show();
            player->close();
            player = nullptr;
        });
        this->hide();
    });

    // 删除存档
    connect(pickSaveWidget,&pickSave::deleteMap,this,[=](int MapId){
        // 要在文件里也删了.不可能只是做个界面罢了.
        user->deleteuserMapFolder(MapId);
    });
    // 刷新地图列表.
    connect(pickSaveWidget,&pickSave::refreshMapList,this,[=](){
        pickSaveWidget->readMap(this->user);
    });
    // 重新设置存档游戏
    connect(pickSaveWidget,&pickSave::reSet,this,[=](int MapId){
        this->CurrentMapID = MapId;
        this->scrollWidget->show();
        this->pickSaveWidget->hide();
        // 设置界面要与文件保持一致
        this->setting_data = setting->readSettingDataFromFolder(QString(projectPath)+"data/game/"+user->getUsername()+"/"+QString::number(CurrentMapID)+"/"+user->getUsername()+".config");
        //Setting::debugSettingData(setting_data);
        setting->writeSettingDataToComponent(setting_data);
    });
    // 拿到设置结构体
    connect(setting,&Setting::emitSettingData,this,[=](settingData* setting){
        this->setting_data = setting;
        user->writeSettingData(QString(projectPath)+"data/game/"+user->getUsername()+"/"+QString::number(CurrentMapID)+"/"+user->getUsername()+".config",this->setting_data);
    });
}

startGame::~startGame(){
    delete game;
}

void startGame::setUser(userData * user)
{
    this->user = user;
    beginwidget->setUser(this->user);
    game->setUser(this->user);

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


void startGame::createSetting()
{
    // 设置界面
    //     设置界面放在滚动区里.

    this->scrollWidget = new QScrollArea(this);
    this->setting = new Setting();
    scrollWidget->setWidget(setting);
    scrollWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollWidget->hide();
}

