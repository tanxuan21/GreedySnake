#include "game.h"
#include "ui_game.h"
#include <QTimer>
#include <QKeyEvent>
#include "./gameinfo.h"
//#include "./snakeunit.h"
#include "tool/tool.h"
#include "gameprops.h"
Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    this->infoWidget = new gameInfo(this);
    this->infoWidget->show();
    this->infoWidget->move(300,300);
//    this->infoWidget->setStyleSheet("border: 1px solid black;background-color: white;");
    // 设置窗口title
    this->setWindowTitle("游戏");
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Game::update);
    timer->start(5);

    timer->stop();



    // 游戏信息界面
    // 保存游戏
    connect(infoWidget,&gameInfo::save_and_quit,this,[=](){
        emit backToBegin();
        qDebug()<<"当前地图编号"<<MapID;
        if(this->MapID>=0){
            user->saveMap(MapID,this->map,this->setting,this->record);
        }
        else{
          this->MapID = user->createNewMapFolder();
          user->saveMap(MapID,this->map,this->setting,this->record);
          this->MapID = -1;
        }
        release();
    });
    // 继续游戏
    connect(infoWidget,&gameInfo::continueGame,this,[=](){
        switchPause();
    });
    connect(infoWidget,&gameInfo::reStart,this,[=](){
        release();
        init();
        switchPause();
        // 重新开始游戏
    });
    connect(infoWidget,&gameInfo::exit,this,[=](){
        release();
        emit backToBegin();
    });
}

Game::~Game()
{
    delete ui;
}

void Game::setUser(userData *user)
{
    this->user = user;
}

void Game::setGameOption(int MapID, settingData *setting, Map *map, Record *record)
{
    this->MapID = MapID;
    this->setting = setting;
    this->record = record;
    this->map  = map;
    Setting::debugSettingData(this->setting);
    // 初始化全游戏.

    init(); // 目前里面只有蛇身测试代码
}
void Game::init()
{
//    this->snack->setStyleSheet("background-color:black;");
    int initLength = 2;
    for(int i= 0;i<=initLength;i++){
        gameProps *s = new gameProps(ui->gameArea);
//        s->move(2*UnitSize+UnitSize*(i),2*UnitSize);
//        s->setPos(QPoint(2+i,2));// 这个点很重要.后面经常使用.
        s->move(2*UnitSize,2*UnitSize);
        s->setPos(QPoint(2,2));
        s->setDirection(Qt::Key_D);// 默认一开始向右走.
//        s->setColor(QColor(200,200,0));
        s->setColor(QColor(10,200,100));
        s->show();
        if(i==initLength){
            this->snackHead = s;
        }
        else if(i==0){
            this->snackTail = s;
            //this->snackTail->move(this->snackHead->x(),this->snackHead->y());
        }
        else{
            snack.enqueue(s);
        }
    }
//    snackHead->setColor(QColor(40,0,200));
    // 蛇头蛇尾单独提出来.它是判断游戏动作的重要对象.

    // 蛇身的每一个单元都有一个Qt键盘ID值作为方向.
    // 游戏每一帧按照这个方向更新他们的位置.
    // 蛇头碰到边线,整条蛇的方向更新为它前一个单元的方向.蛇头的方向就是键盘事件获取的方向.

    // 队列也可以当作数组操作.
    // 队头是数组尾.队尾是数组头.
    this->snackHead->setDirection(Qt::Key_A);
    this->snackTail->setDirection(Qt::Key_A);
    setUnitSize((this->height()-120)/this->setting->mapHeight);// 动态根据尺寸设置地图单元大小.
    // 蛇的方向置一个默认值
    this->NextX = 1;this->NextY= 0;
    snackHead->setDirection(0);
}
void Game::on_pushButton_clicked()
{

}

void Game::setUnitSize(int size)
{
    this->UnitSize = size;
    for(int i= 0;i<snack.length();i++){// 每个单元重新设置尺寸
        snack[i]->setSize(UnitSize);
        snack[i]->move(snack[i]->getPoint().x()*UnitSize,snack[i]->getPoint().y()*UnitSize);
    }
    this->snackHead->setSize(UnitSize);
    this->snackHead->move(this->snackHead->getPoint().x()*UnitSize,this->snackHead->getPoint().y()*UnitSize);
    this->snackTail->setSize(UnitSize);
    this->snackTail->move(this->snackTail->getPoint().x()*UnitSize,this->snackTail->getPoint().y()*UnitSize);
    for(int i= 0;i<foodList.length();i++){
        foodList[i]->setSize(UnitSize);
        foodList[i]->move(foodList[i]->getPoint().x()*UnitSize,foodList[i]->getPoint().y()*UnitSize);
    }
    ui->gameArea->setFixedSize(this->UnitSize * setting->mapWidth,this->UnitSize * setting->mapHeight);//尺寸
    ui->gameArea->setSize(this->UnitSize);

}


void Game::generalFood()
{
    if(this->foodList.length()<setting->foodCount){// 小于就生成
        QPoint gamePos = QPoint(tool::randomInt(0,setting->mapWidth-1),tool::randomInt(0,setting->mapHeight-1));
        gameProps *pro = new gameProps(ui->gameArea);
        pro->setColor(QColor(200,100,100));
        pro->setSize(this->UnitSize);
        pro->setPos(gamePos);
        pro->move(gamePos.x()*this->UnitSize,gamePos.y()*this->UnitSize);
        pro->show();
        foodList.append(pro);
//        qDebug()<<gamePos.x()<<gamePos.y();
    }
}


void Game::calculateNextX_Y()
{
    //if(snackHead->pos().y()%this->UnitSize==0 && snackHead->pos().x()%this->UnitSize==0){// 如果蛇头到格子边缘
        // 蛇头在自己的位置创建一个单元.
        gameProps *NewSnack = new gameProps(ui->gameArea);
        NewSnack->setColor(QColor(10,200,100));
        NewSnack->setDirection(this->snackHead->getDirection());// 这个信息很重要.它最终给到蛇尾,确定蛇尾的走向.
        NewSnack->setPos(snackHead->getPoint());
        NewSnack->setSize(this->UnitSize);
        NewSnack->move(snackHead->x(),snackHead->y());
        snack.enqueue(NewSnack);
        NewSnack->show();

        snackHead->setPos(QPoint(snackHead->pos().x()/this->UnitSize,snackHead->pos().y()/this->UnitSize));// 设置蛇头的数据位置
        int CollisionID = collision();
        if(CollisionID == -1){// 啥也没碰到才删队列.
            gameProps *gp = snack.dequeue();
            this->snackTail->setDirection(gp->getDirection());
            gp->close();
        }
        else if(CollisionID == 1){

        }
        // 检测碰撞.是否与食物碰撞,是否与墙体、自己碰撞
        // 根据读取的键盘方向设置蛇头下一帧的方向
        QPoint dir = KeydirToDirection(this->snackHead);
//        QPoint dir1 = KeydirToDirection(snack[0]);
        if(dir.x()!=0 || dir.y()!=0){
            this->NextX = dir.x();
            this->NextY = dir.y();
        }
        if(snack.length()){
            this->snackTail->move(snack[0]->x(),snack[0]->y());
            this->snackTail->setPos(snack[0]->getPoint());
        }
}
QPoint Game::KeydirToDirection(gameProps *p)
{

    if(p->getDirection()==Qt::Key_Up || p->getDirection() == Qt::Key_W){
        return QPoint(0,-1);
    }
    else if(p->getDirection()==Qt::Key_Down || p->getDirection() == Qt::Key_S){
        return QPoint(0,1);
    }
    else if(p->getDirection()==Qt::Key_Left ||p->getDirection()== Qt::Key_A){
        return QPoint(-1,0);
    }
    else if(p->getDirection()==Qt::Key_Right || p->getDirection() == Qt::Key_D ){
        return QPoint(1,0);
    }
    return QPoint(0,0);
}

void Game::updatePosition()
{
    this->snackHead->move(this->snackHead->x() +this->NextX,this->snackHead->y()+this->NextY);// 蛇头移动就好

    if(snack.length()){
        QPoint snackTailDir = KeydirToDirection(snack[0]);
        //qDebug()<<snackTailDir.x()<<snackTailDir.y();
        if(snackTailDir.x()!=0 || snackTailDir.y() !=0){
            this->NextX_ = snackTailDir.x();
            this->NextY_ = snackTailDir.y();
        }
        snack[0]->hide();
        this->snackTail->move(this->snackTail->x()+NextX_,this->snackTail->y()+NextY_);
    }
    else{
        this->snackTail->move(this->snackHead->x() +this->NextX,this->snackHead->y()+this->NextY);
    }

}
void Game::failed()
{
    /*
    if(snackHead->pos().x()+this->UnitSize > ui->gameArea->width() ||
       snackHead->pos().x() < 0 ||
       snackHead->pos().y() + this->UnitSize > ui->gameArea->height() ||
       snackHead->pos().y() < 0){

    }
    */


    if(snackHead->pos().y()<0){
        if(setting->upwall){
            switchPause();
            this->infoWidget->setText("失败");
        }
        else{
            this->snackHead->move(this->snackHead->x(),ui->gameArea->height());
        }
    }
    else if(snackHead->pos().y()+this->UnitSize > ui->gameArea->height()){
        if(setting->downwall){
            switchPause();
            this->infoWidget->setText("失败");
        }
        else{
            this->snackHead->move(this->snackHead->x(),0-this->UnitSize);
        }
    }
    else if(snackHead->pos().x()<0){
        if(setting->leftwall){
            switchPause();
            this->infoWidget->setText("失败");
        }
        else{
            this->snackHead->move(ui->gameArea->width(),this->snackHead->y());
        }
    }
    else if(snackHead->pos().x()+this->UnitSize > ui->gameArea->width()){
        if(setting->rightwall){
            switchPause();
            this->infoWidget->setText("失败");
        }
        else{
            this->snackHead->move(0-this->UnitSize,this->snackHead->y());
        }
    }

}


// ===============================================================================================
// ===============================================================================================
// 游戏每帧调用一次
void Game::update()
{


    updatePosition();
    // 如果碰到边缘.
    if(snackHead->pos().y()%this->UnitSize==0 && snackHead->pos().x()%this->UnitSize==0){
        touchingEdg = true;
    }
    else{
        touchingEdg = false;
    }
    if(touchingEdg == true && lasttouchingEdg == false){
        generalFood();// 生成食物
        calculateNextX_Y(); // 计算下一帧位置

        failed();
    }
    this->lasttouchingEdg = this->touchingEdg;
}
// ===============================================================================================
// ===============================================================================================


// 碰撞
int Game::collision()
{
    if(this->snackHead->getDirection()==Qt::Key_Up || this->snackHead->getDirection() == Qt::Key_W){// 向上,上边缘来检测
        int val = this->snackHead->pos().y()/this->UnitSize;
        for(int i = 0;i<foodList.length();i++){
            if(val == (foodList[i]->getPoint().y()+1) && (this->snackHead->pos().x()/this->UnitSize == foodList[i]->getPoint().x())){
                foodList[i]->close();
                foodList.removeAt(i);
                return 1;
            }
        }
    }
    else if(this->snackHead->getDirection()==Qt::Key_Down || this->snackHead->getDirection() == Qt::Key_S){// 向下,下边缘检测
        int val = this->snackHead->pos().y()/this->UnitSize;
        for(int i = 0;i<foodList.length();i++){
            if(val == foodList[i]->getPoint().y()-1 && (this->snackHead->pos().x()/this->UnitSize == foodList[i]->getPoint().x())){
                foodList[i]->close();
                foodList.removeAt(i);
                return 1;
            }
        }
    }
    else if(this->snackHead->getDirection()==Qt::Key_Left ||this->snackHead->getDirection()== Qt::Key_A){
        int val = this->snackHead->pos().x()/this->UnitSize;
        for(int i = 0;i<foodList.length();i++){
            if(val == this->foodList[i]->getPoint().x()+1 && (this->snackHead->pos().y()/this->UnitSize == foodList[i]->getPoint().y())){
                foodList[i]->close();
                foodList.removeAt(i);
                return 1;
            }
        }
    }
    else if(this->snackHead->getDirection()==Qt::Key_Right || this->snackHead->getDirection() == Qt::Key_D ){
        int val = this->snackHead->pos().x()/this->UnitSize;
        for(int i = 0;i<foodList.length();i++){
            if(val == this->foodList[i]->getPoint().x()-1 && (this->snackHead->pos().y()/this->UnitSize == foodList[i]->getPoint().y())){
                foodList[i]->close();
                foodList.removeAt(i);
                return 1;
            }
        }
    }
    return -1;
}


// 释放内存.关闭不需要的widget
void Game::release()
{
    for(int i = 0;i<this->foodList.length();i++){
        foodList[i]->close();
//        delete foodList[i];
    }
    this->foodList.clear();
    int l = snack.length();
    for(int i = 0;i<l;i++){
        gameProps *g= snack.dequeue();
        qDebug()<<g<<snack.length();
        g->close();
    }

    this->snackHead->close();
    this->snackTail->close();
}

// *****************************************************************
// Qt事件
void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==32)
    {
        switchPause();
    }
    this->snackHead->setDirection(event->key());
}

void Game::paintEvent(QPaintEvent *)
{
//    QPainter painter = QPainter(ui->gameArea);
//    painter.setBrush(Qt::white);
//    painter.drawRect(0,0,100,100);
//    QPainter painter1 = QPainter(this);
//    painter1.setBrush(Qt::white);
//    painter1.drawRect(400,400,100,100);
}

void Game::resizeEvent(QResizeEvent *event)
{
    //infoWidget剧中
    this->infoWidget->move((this->width()-this->infoWidget->width())/2,(this->height()-this->infoWidget->height())/2);
    if(this->setting){// 设置撑满策略.需要地图尽可能填满整个布局组件.
        /*
        // 在我的计算机上,窗口不可能是纵向长方形!(这里为了工作量,我不实现在不同屏幕尺寸的resize情况了.)
        if(this->height()>=this->width() && this->setting->mapHeight >= this->setting->mapWidth){// 同是纵向长方形,

        }
        */
        if(this->height() <= this->width() && this->setting->mapHeight <= this->setting->mapWidth){// 同是横向长方形
            // 窗口更扁 纵向撑满.
            if(this->height()/this->width() <= this->setting->mapHeight / this->setting->mapWidth){
                setUnitSize((this->height()-120)/this->setting->mapHeight);
            }
            // 窗口更纵 横向撑满
            else{
                setUnitSize((this->width()-120)/this->setting->mapWidth);
            }
        }
        if(this->height()<this->width() && this->setting->mapHeight > this->setting->mapWidth){
            // 窗口是横向长方形,地图是纵向长方形
            // 这种情况地图的高撑满窗口的高就好了.
            setUnitSize((this->height()-120)/this->setting->mapHeight);

        }

        /*
        if(this->height()>this->width() && this->setting->mapHeight < this->setting->mapWidth){
            // 窗口是纵向长方形,地图是横向长方形
            // 这种情况地图的宽撑满窗口的宽就好了.
            setUnitSize((this->width()-120)/this->setting->mapWidth);
        }
        */
        //setUnitSize((this->height()-120)/this->setting->mapHeight);
    }// 动态根据尺寸设置地图单元大小.
}

