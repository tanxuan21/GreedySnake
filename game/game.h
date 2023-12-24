#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPushButton>
#include "./snakeunit.h"
#include <QQueue>
#include <QTimer>
#include <QTime>
#include <QTextStream>
#include <QLabel>

#include <QList>
#include <QPair>

#include "config.h"
#include "./gameinfo.h"
#include "dataHandler/userdata.h"
#include "./gameprops.h"

#include <iostream>
namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    void setSettingData(settingData* s){this->setting = s;}
    void setMapID(int i){this->MapID = i;}
    void setUser(userData *user);
    void setGameOption(int MapID,settingData *setting,Map *map,Record *record);

    bool isOppositeDirection(int dir1, int dir2);

    //生成墙面
    void generateBorder();
    //声明获取相对时间函数
    int getCurrentTime() const {
        return QTime::currentTime().msecsSinceStartOfDay();
    }

public slots:
    void failed();


private:
    Ui::Game *ui;
    // 测试
    gameProps *pros;


    // 用户数据
    userData *user;


    // 游戏数据区
    gameProps *snackHead;
    gameProps *snackTail;

    settingData *setting;
    int MapID  = -1;

    Map *map;
    Record *record;
    bool lasttouchingEdg = false;
    bool touchingEdg  =false;// 是否碰到每个格子边.因为游戏帧过于密集,可能在边界重复调用update里面的函数.需要做防抖.
    bool hasResized = false;// 继续(开始)是否resize过.
    gameProps *lastTail;
    // 蛇队列
    QQueue<gameProps*> snack;
    // 界面
    gameInfo* infoWidget;
    int UnitSize = 50;
    void setUnitSize(int size);
    // ==================游戏主流程========================
    // 游戏时钟
    QTimer *timer;
    bool IsPause = true;
    bool spacePause = false;
    // 切换暂停继续
    void switchPause(){
        IsPause = !IsPause;
        if(IsPause){timer->start();infoWidget->hide();}
        else{timer->stop();infoWidget->show();}
    }
    void update();// 游戏每帧调用

    void init();// 根据设置对象,地图对象初始化游戏设置.
    int collision();// 返回1说明碰到食物.返回0说明碰到障碍、边界、自己等等.反正,返回0游戏结束.返回1吃到食物.
    void updatePosition();

    bool isFailed;
    bool isAuto;

    // 设置整个蛇的颜色
    void setSnakeColor(const QColor &color);

    void release();// 释放所有资源.
    //====================================================
    // ================API====================
    // 控制蛇移动
    //int direction = Qt::Key_Up;//方向.蛇这一帧怎么走根据这个值来判断
    int headNextX = 1,headNextY = 0;
    int tailNextX = 1,tailNextY = 0;
    QPoint currentDirection;        // 保存当前方向的成员变量
    qint64 lastInputTime;  // 记录上次输入的时间
    QPoint lastInputDirection;  // 记录最后一个合法的方向输入

    void calculateNextX_Y();
    // 生成食物
    QList<gameProps *> foodList;
    void generalFood();

    QPoint KeydirToDirection(gameProps *p);
    //生成得分
    int score;
    QLabel *scoreLabel;  //得分显示

    // 生成障碍物
    QList<gameProps *> blockList;
    void generalBlockList();
    // ====================工具函数=======================
    // 屏幕中的像素点 -> 位置信息
    QPoint pixelToPos(QPoint pixel);
    // 位置信息 -> 屏幕中的像素点
    QPoint PosToPixel(QPoint Pos);
    QPushButton *pauseButton;
    bool spacePaused;
    //用来录制用户动作
    QList<QPair<int, int>> userActions; // 时间戳和用户操作的对应关系
    int startRelativeTime; // 起始相对时间

    //
    void recordUserAction(int key);
    void saveRecord();
    void loadRecord();

private slots:
    void updateScoreLabel(int score);  // 更新得分标签的槽函数
signals:
    void backToBegin();
    //传输分数
    void scoreChanged(int score);

protected:
    void keyPressEvent(QKeyEvent *);
    void simulateKeyPress(int asciiCode);
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent *);
private:
    void resize();
};

#endif // GAME_H
