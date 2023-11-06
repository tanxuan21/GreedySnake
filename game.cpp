#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    // 设置窗口title
    this->setWindowTitle("游戏");
}

Game::~Game()
{
    delete ui;
}

void Game::on_pushButton_clicked()
{
    emit backToBegin();
}

