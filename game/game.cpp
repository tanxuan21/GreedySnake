#include "game.h"
#include "ui_game.h"
#include <QTimer>
#include <QKeyEvent>
//#include "./snakeunit.h"
Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{

    ui->setupUi(this);
    // 设置窗口title
    this->setWindowTitle("游戏");
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Game::update);
    timer->start(10);

    timer->stop();
    // 蛇身测试代码
    this->snackU = new SnakeUnit(ui->gameArea);
//    this->snack->setStyleSheet("background-color:black;");
    this->snackU->move(100,100);
    this->snackU->setSize(20);
    this->snackU->show();



}

Game::~Game()
{


    delete ui;
}

void Game::on_pushButton_clicked()
{
    emit backToBegin();
}
// 游戏每帧调用一次
void Game::update()
{
    snackU->move(snackU->x()+1,snackU->y()+1);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==32){
        switchPause();
    }
}

void Game::paintEvent(QPaintEvent *)
{
    QPainter painter = QPainter(ui->gameArea);
    painter.setBrush(Qt::white);
    painter.drawRect(0,0,100,100);
    QPainter painter1 = QPainter(this);
    painter1.setBrush(Qt::white);
    painter1.drawRect(400,400,100,100);
}

