#include "recordplayer.h"
#include "ui_recordPlayer.h"// cao,这个头文件也要改哈哈
#include <QTimer>
#include <QKeyEvent>
#include "./gameinfo.h"
//#include "./snakeunit.h"
#include "tool/tool.h"
#include "gameprops.h"
#include <random>
#include <iostream>
recordPlayer::recordPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recordPlayer)
{
    ui->setupUi(this);
    this->infoWidget = new gameInfo(this);
    this->infoWidget->show();
    this->infoWidget->move(300,300);
    //    this->infoWidget->setStyleSheet("border: 1px solid black;background-color: white;");
    // 设置窗口title
    // 现在的难度就是游戏难度.也就是速度.我的窗口是可以resize的.所以它的速度也要动态调整.
    // 要求是难度d = 1/t. t为走过一格的时间.
    this->setWindowTitle("游戏");
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&recordPlayer::update);
    timer->start(700000);
    timer->stop();

    // 游戏信息界面
    // 保存游戏
    connect(infoWidget,&gameInfo::save_and_quit,this,[=](){
        // 当前地图是存在的,就保存覆盖原有的.
    });
    // 继续游戏
    connect(infoWidget,&gameInfo::continueGame,this,[=](){
        //switchPause();
    });

    connect(infoWidget,&gameInfo::reStart,this,[=](){
//        release();
//        init();
//        switchPause();
        // 重新开始游戏
    });
    connect(infoWidget,&gameInfo::exit,this,[=](){
        release();
        emit rec_backToBegin();
    });
}

recordPlayer::~recordPlayer()
{
    delete ui;
}

void recordPlayer::setUser(userData *user)
{
    this->user = user;
}

void recordPlayer::setGameOption(int MapID, settingData *setting, Map *map, Record *record)
{
    this->MapID = MapID;
    this->setting = setting;
    this->record = record;
    this->map = map;
//    Record::debug(record);
    init(); // 目前里面只有蛇身测试代码
}
// 初始化全部游戏
void recordPlayer::init()
{

//    for(int i = 0;i<this->map->foodArry.length();i++){
//        gameProps *food = new gameProps(ui->gameArea);
//        food->setColor(QColor(200,100,100));
//        food->setSize(this->UnitSize);
//        food->setPos(QPoint(this->map->foodArry[i].x(),this->map->foodArry[i].y()));
//        food->move(this->map->foodArry[i].x()*this->UnitSize,this->map->foodArry[i].y()*this->UnitSize);
//        food->show();
//        this->foodList.append(food);
//    }

    for(int i = 0;i<this->map->blockArry.length();i++){// 障碍物是原来的,但是地图的其他东西不是.
        gameProps *block = new gameProps(ui->gameArea);
        block->setColor(QColor(200,200,200));
        block->setSize(this->UnitSize);
        block->setPos(QPoint(this->map->blockArry[i].x(),this->map->blockArry[i].y()));
        block->move(this->map->blockArry[i].x()*UnitSize,this->map->blockArry[i].y()*UnitSize);
        block->show();
        blockList.append(block);
    }
    // record是要初始的地图!!但是我们的地图保存的是完成的了.所以要重新构造地图
    map = Map::createMap(this->setting);
    for(int i = 0;i<this->map->snack.length();i++){
        gameProps *s = new gameProps(ui->gameArea);
        s->move(this->map->snack[i].x*UnitSize,this->map->snack[i].y*UnitSize);
        s->setDirection(this->map->snack[i].dir);
        s->setPos(QPoint(this->map->snack[i].x,this->map->snack[i].y));
        s->setColor(QColor(10,200,100));
        s->show();
        this->snack.enqueue(s);
    }
    gameProps *sH = new gameProps(ui->gameArea);
    sH->move(this->map->snackHead.x*UnitSize,this->map->snackHead.y*UnitSize);
    sH->setPos(QPoint(this->map->snackHead.x,this->map->snackHead.y));
    sH->setColor(QColor(10,200,100));
    sH->show();
    this->snackHead = sH;
    gameProps *sT = new gameProps(ui->gameArea);
    sT->move(this->map->snackTail.x*UnitSize,this->map->snackTail.y*UnitSize);
    sT->setPos(QPoint(this->map->snackTail.x,this->map->snackTail.y));
    sT->setColor(QColor(10,200,100));
    sT->show();
    this->snackTail = sT;

    this->snackHead->setDirection(this->map->snackHead.dir);
    this->snackTail->setDirection(this->map->snackTail.dir);

    QPoint NextH = this->KeydirToDirection(snackHead);
    QPoint NextT = this->KeydirToDirection(snackTail);
    this->headNextX = NextH.x();this->headNextY= NextH.y();
    this->tailNextX = NextT.x();this->tailNextY= NextT.y();
    this->resize();
}


void recordPlayer::setUnitSize(int size)
{
    this->UnitSize = size;
    this->timer->setInterval(((1/double(this->setting->gameDifficult))*1000)/this->UnitSize);
    for(int i= 0;i<snack.length();i++){// 每个单元重新设置尺寸
        snack[i]->setSize(UnitSize);
        snack[i]->move(snack[i]->getPoint().x()*UnitSize,(snack[i]->getPoint().y())*UnitSize);
    }
    this->snackHead->setSize(UnitSize);
    this->snackHead->move(this->snackHead->getPoint().x()*UnitSize,this->snackHead->getPoint().y()*UnitSize);
    this->snackTail->setSize(UnitSize);
    this->snackTail->move(this->snackTail->getPoint().x()*UnitSize,this->snackTail->getPoint().y()*UnitSize);
    for(int i= 0;i<foodList.length();i++){
        foodList[i]->setSize(UnitSize);
        foodList[i]->move(foodList[i]->getPoint().x()*UnitSize,foodList[i]->getPoint().y()*UnitSize);
    }
    for(int i= 0;i<blockList.length();i++){
        blockList[i]->setSize(UnitSize);
        blockList[i]->move(blockList[i]->getPoint().x()*UnitSize,blockList[i]->getPoint().y()*UnitSize);
    }
    ui->gameArea->setFixedSize(this->UnitSize * setting->mapWidth,this->UnitSize * setting->mapHeight);//尺寸
    ui->gameArea->setSize(this->UnitSize);

}


/*
void recordPlayer::generalFood()
{
    if(this->foodList.length()<setting->foodCount){// 小于就生成
        QPoint gamePos;
        bool isOnSnack = true;
        // 一直生成知道不在蛇身上为止.
        // 这样做不好.蛇遍布地图时要跑很久才会出来正确的食物位置.
        // 需要记录下来蛇的坐标数组.
        do{
            int i = 0,j=0;
            gamePos = QPoint(tool::randomInt(0,setting->mapWidth-1),tool::randomInt(0,setting->mapHeight-1));
            //            qDebug()<<gamePos.x()<<gamePos.y();
            for(;i < snack.length();i++){
                if(snack[i] -> getPoint().x() == gamePos.x() && snack[i]->getPoint().y() == gamePos.y()){
                    qDebug()<<"on";
                    break;
                }
            }

            for(;j < blockList.length();j++){
                if(blockList[j] -> getPoint().x() == gamePos.x() && blockList[j]->getPoint().y() == gamePos.y()){
                    qDebug()<<"on";
                    break;
                }
            }
            if(i == snack.length() && j == blockList.length()){
                isOnSnack = false;
            }
        }while(isOnSnack);
        gameProps *food = new gameProps(ui->gameArea);
        food->setColor(QColor(200,100,100));
        food->setSize(this->UnitSize);
        food->setPos(gamePos);
        food->move(gamePos.x()*this->UnitSize,gamePos.y()*this->UnitSize);
        food->show();
        foodList.append(food);
    }
}

*/
// 生成障碍物数组
//void recordPlayer::generalBlockList()
//{
//    // 生成障碍物
//    for(int i = 0;i<setting->blockCount;i++){
//        gameProps *block = new gameProps(ui->gameArea);
//        block->setColor(QColor(200,200,200));
//        block->setSize(this->UnitSize);
//        QPoint p;
//        p.rx() = tool::randomInt(0,this->setting->mapWidth-1);
//        p.ry() = tool::randomInt(0,this->setting->mapHeight-1);
//        block->setPos(p);
//        block->move(p.x()*UnitSize,p.y()*UnitSize);
//        block->show();
//        blockList.append(block);
//    }
//}

void recordPlayer::calculateNextX_Y()
{

    this->snackHead -> setDirection(record->recData[frameNumber]->sb.dir);// 方向读进来
    QPoint gamePos;
    for(int i = 0;i<record->recData[frameNumber]->foodArr.length();i++){
        gamePos.rx() = record->recData[frameNumber]->foodArr[i]->x;
        gamePos.ry() = record->recData[frameNumber]->foodArr[i]->y;
        bool isContain = false;

        for(int j = 0;j<foodList.length();j++){
            if(foodList[j]->getPoint().x() == gamePos.x() && foodList[j]->getPoint().y() == gamePos.y()){
                isContain = true;
            }
        }
        if(!isContain){
            gameProps *food = new gameProps(ui->gameArea);
            food->setColor(QColor(200,100,100));
            food->setSize(this->UnitSize);
            food->setPos(gamePos);
            food->move(gamePos.x()*this->UnitSize,gamePos.y()*this->UnitSize);
            food->show();
            foodList.append(food);
            qDebug()<<gamePos.x() << gamePos.y();
        }
    }
    // 蛇头在自己的位置创建一个单元.
    QPoint p = QPoint(snackHead->pos().x()/this->UnitSize,snackHead->pos().y()/this->UnitSize);
    snackHead->setPos(p);// 设置蛇头的数据位置

    gameProps *NewSnack = new gameProps(ui->gameArea);
    NewSnack->setColor(QColor(10,200,100));
    NewSnack->setDirection(this->snackHead->getDirection());// 这个信息很重要.它最终给到蛇尾,确定蛇尾的走向.
    NewSnack->setPos(snackHead->getPoint());
    NewSnack->setSize(this->UnitSize);
    NewSnack->move(snackHead->x(),snackHead->y());
    snack.enqueue(NewSnack);
    NewSnack->show();

    // 检测碰撞.是否与食物碰撞,是否与墙体、自己碰撞
    int CollisionID = collision();
    if(CollisionID == -1){// 啥也没碰到才删队列.
        gameProps *gp = snack.dequeue();// 删掉蛇尾
        this->snackTail->setDirection(gp->getDirection());

        QPoint snackTailDir = KeydirToDirection(snack[0]);// 蛇身最后一个单元的方向作为蛇尾的移动方向.
        if(snackTailDir.x()!=0 || snackTailDir.y() !=0){
            this->tailNextX = snackTailDir.x();
            this->tailNextY = snackTailDir.y();
        }
        snack[0]->hide();

        this->lastTail = gp;
        gp->close();
    }
    else if(CollisionID == 1){// 吃到食物.加分.

    }
    else if(CollisionID == 0){// 失败.退出.
        this->switchPause();
        failed();
    }

    // 根据读取的键盘方向设置蛇头下一帧的方向
    QPoint dir = KeydirToDirection(this->snackHead);

    // 保存存档

//    frameData *fram = new frameData();// 创建一个帧对象.保存当前帧的键盘信息和食物信息
//    fram->sb.x = snackHead->getPoint().x();
//    fram->sb.y = snackHead->getPoint().y();
//    fram->sb.dir = snackHead->getDirection();

//    for(int i = 0;i<foodList.length();i++){
//        food *fd = new food();
//        fd->value = 1;
//        fd->x = foodList[i]->getPoint().x();
//        fd->y = foodList[i]->getPoint().y();
//        fram->foodArr.push_back(fd);
//    }
//    this->record->recData.push_back(fram);
    // 从存档设置当前帧的操作.

    // 边界条件的判断
    if(dir.x()!=0 || dir.y()!=0){
        this->headNextX = dir.x();
        this->headNextY = dir.y();
    }
    if(snack.length()){// 蛇尾移动到前一个蛇身上.这一步非常重要.否则蛇尾不能正确的跟上蛇.因为蛇身长度会变化.
        this->snackTail->move(snack[0]->x(),snack[0]->y());
        this->snackTail->setPos(snack[0]->getPoint());
    }
    this->hasResized = false;

}
// =======================工具函数=========================
QPoint recordPlayer::KeydirToDirection(gameProps *p)
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



// 像素转位置
QPoint recordPlayer::pixelToPos(QPoint pixel)
{
    return QPoint(pixel.x()/this->UnitSize,pixel.y()/this->UnitSize);
}
// 位置转像素
QPoint recordPlayer::PosToPixel(QPoint Pos)
{
    return QPoint(Pos.x()*this->UnitSize,Pos.y()*this->UnitSize);
}
//========================================================


void recordPlayer::updatePosition()
{
    this->snackHead->move(this->snackHead->x() +this->headNextX,this->snackHead->y()+this->headNextY);// 蛇头移动就好

    if(snack.length()){// 蛇有长度

        this->snackTail->move(this->snackTail->x()+tailNextX,this->snackTail->y()+tailNextY);
    }
    else{// 移到蛇头.蛇头蛇尾同位置.
        this->snackTail->move(this->snackHead->x() +this->headNextX,this->snackHead->y()+this->headNextY);
    }

}
void recordPlayer::failed()
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
void recordPlayer::update()
{

    // 如果碰到边缘.
    if(snackHead->pos().y()%this->UnitSize==0 && snackHead->pos().x()%this->UnitSize==0){
        touchingEdg = true;
    }
    else{
        touchingEdg = false;
    }
    if(touchingEdg == true && lasttouchingEdg == false){
        if(frameNumber == record->recData.length()){
            failed();// 不能再跑了.已经到头了.
            switchPause();
            return;
        }
        else{
            if(!hasResized){
                calculateNextX_Y(); // 计算下一帧位置
            }
            hasResized = false;
            failed();
            frameNumber ++;
        }
    }
    this->lasttouchingEdg = this->touchingEdg;
    updatePosition(); //我在结束才调用更新位置函数.这里看看未来会不会出现bug.
    // 这里是为了resize时重置一切信息时使用.
}
// ===============================================================================================
// ===============================================================================================


// 碰撞
// 返回1说明吃到食物
// 返回0说明碰到障碍物或自身.游戏结束
// 返回-1正常行进.啥也没碰到.
int recordPlayer::collision()
{
    int y = this->snackHead->pos().y()/this->UnitSize;
    int x = this->snackHead->pos().x()/this->UnitSize;
    if(this->snackHead->getDirection()==Qt::Key_Up || this->snackHead->getDirection() == Qt::Key_W){// 向上,上边缘来检测
        // 检测与蛇自己的碰撞
        for(int i = 0;i<snack.length();i++){
            if(y == snack[i]->getPoint().y()+1 && (this->snackHead->pos().x()/this->UnitSize == snack[i]->getPoint().x())){
                return 0;
            }
        }
        // 检测蛇与障碍物的碰撞.
        for(int i = 0;i<blockList.length();i++){
            if(y == blockList[i]->getPoint().y()+1 && (this->snackHead->pos().x()/this->UnitSize == blockList[i]->getPoint().x())){
                return 0;
            }
        }
        // 检测foodlist的碰撞
        for(int i = 0;i<foodList.length();i++){
            if(y == (foodList[i]->getPoint().y()+1) && (this->snackHead->pos().x()/this->UnitSize == foodList[i]->getPoint().x())){
                foodList[i]->close();
                foodList.removeAt(i);
                return 1;
            }
        }
    }
    else if(this->snackHead->getDirection()==Qt::Key_Down || this->snackHead->getDirection() == Qt::Key_S){// 向下,下边缘检测
        for(int i = 0;i<snack.length();i++){
            if(y == snack[i]->getPoint().y()-1 && (this->snackHead->pos().x()/this->UnitSize == snack[i]->getPoint().x())){
                return 0;
            }
        }
        for(int i = 0;i<blockList.length();i++){
            if(y == blockList[i]->getPoint().y()-1 && (this->snackHead->pos().x()/this->UnitSize == blockList[i]->getPoint().x())){
                return 0;
            }
        }
        for(int i = 0;i<foodList.length();i++){
            if(y == foodList[i]->getPoint().y()-1 && (this->snackHead->pos().x()/this->UnitSize == foodList[i]->getPoint().x())){
                foodList[i]->close();
                foodList.removeAt(i);
                return 1;
            }
        }
    }
    else if(this->snackHead->getDirection()==Qt::Key_Left ||this->snackHead->getDirection()== Qt::Key_A){

        for(int i = 0;i<snack.length();i++){
            if(x == this->snack[i]->getPoint().x()+1 && (this->snackHead->pos().y()/this->UnitSize == snack[i]->getPoint().y())){
                return 0;
            }
        }
        for(int i = 0;i<blockList.length();i++){
            if(x == blockList[i]->getPoint().x()+1 && (this->snackHead->pos().y()/this->UnitSize == blockList[i]->getPoint().y())){
                return 0;
            }
        }
        for(int i = 0;i<foodList.length();i++){
            if(x == this->foodList[i]->getPoint().x()+1 && (this->snackHead->pos().y()/this->UnitSize == foodList[i]->getPoint().y())){
                foodList[i]->close();
                foodList.removeAt(i);
                return 1;
            }
        }
    }
    else if(this->snackHead->getDirection()==Qt::Key_Right || this->snackHead->getDirection() == Qt::Key_D ){

        for(int i = 0;i<snack.length();i++){
            if(x == this->snack[i]->getPoint().x()-1 && (this->snackHead->pos().y()/this->UnitSize == snack[i]->getPoint().y())){
                return 0;
            }
        }
        for(int i = 0;i<blockList.length();i++){
            if(x == blockList[i]->getPoint().x()-1 && (this->snackHead->pos().y()/this->UnitSize == blockList[i]->getPoint().y())){
                return 0;
            }
        }
        for(int i = 0;i<foodList.length();i++){
            if(x == this->foodList[i]->getPoint().x()-1 && (this->snackHead->pos().y()/this->UnitSize == foodList[i]->getPoint().y())){
                foodList[i]->close();
                foodList.removeAt(i);
                return 1;
            }
        }
    }
    return -1;
}

// 释放内存.关闭不需要的widget
void recordPlayer::release()
{
    // 清理食物数组
    for(int i = 0;i<this->foodList.length();i++){
        foodList[i]->close();
    }
    this->foodList.clear();
    // 清理蛇身队列
    int l = snack.length();
    for(int i = 0;i<l;i++){
        gameProps *g= snack.dequeue();
        g->close();
    }
    // 清理障碍物数组
    for(int i = 0;i<this->blockList.length();i++){
        blockList[i]->close();
    }
    this->blockList.clear();

    // 清理蛇头蛇尾
    this->snackHead->close();
    this->snackTail->close();
}

// *****************************************************************
// Qt事件
void recordPlayer::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==32)
    {
        switchPause();
    }
//    else if(event->key()==Qt::Key_A ||
//            event->key()==Qt::Key_S ||
//            event->key()==Qt::Key_D ||
//            event->key()==Qt::Key_W||
//            event->key()==Qt::Key_Up ||
//            event->key()==Qt::Key_Down ||
//            event->key()==Qt::Key_Left ||
//            event->key()==Qt::Key_Right  ){
//        this->snackHead->setDirection(event->key());
//    }
}

void recordPlayer::paintEvent(QPaintEvent *)
{
    //    QPainter painter = QPainter(ui->gameArea);
    //    painter.setBrush(Qt::white);
    //    painter.drawRect(0,0,100,100);
    //    QPainter painter1 = QPainter(this);
    //    painter1.setBrush(Qt::white);
    //    painter1.drawRect(400,400,100,100);
}

void recordPlayer::resizeEvent(QResizeEvent *event)
{
    this->hasResized = true;
    this->resize();
}

void recordPlayer::resize()
{

    //infoWidget剧中
    this->infoWidget->move((this->width()-this->infoWidget->width())/2,(this->height()-this->infoWidget->height())/2);
    // 设置撑满策略.需要地图尽可能填满整个布局组件.
    if(this->setting){
        /*
        // 在我的计算机上,窗口不可能是纵向长方形!(这里为了工作量,我不实现在不同屏幕尺寸的resize情况了.)
        if(this->height()>=this->width() && this->setting->mapHeight >= this->setting->mapWidth){// 同是纵向长方形,

        }
        */
        if(this->height() <= this->width() && this->setting->mapHeight <= this->setting->mapWidth){// 同是横向长方形
            // 窗口更扁 纵向撑满.
            if(double(this->height())/this->width() <= double(this->setting->mapHeight) / this->setting->mapWidth){
                qDebug()<<"纵向";
                setUnitSize((this->height()-120)/this->setting->mapHeight);
                touchingEdg = true;// resize时根据每个游戏组件对象的的pos属性值来重新设置位置.
                // 但是更新pos只在碰到格子才更新.这时resize,蛇会退回上一个格子.
                // 如果不把touchingEdg设为true,游戏开始运行时,蛇头不会在它后面创建一个蛇身.蛇会断开.
            }
            // 窗口更纵 横向撑满
            else{
                qDebug()<<"横向";
                setUnitSize((this->width()-120)/this->setting->mapWidth);
                touchingEdg = true;
            }
        }
        if(this->height()<this->width() && this->setting->mapHeight > this->setting->mapWidth){
            // 窗口是横向长方形,地图是纵向长方形
            // 这种情况地图的高撑满窗口的高就好了.
            setUnitSize((this->height()-120)/this->setting->mapHeight);
            touchingEdg = true;
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

