#include "begin.h"
#include "ui_begin.h"
#include "./game.h"
begin::begin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::begin)
{
    game = new Game();
    ui->setupUi(this);
    // 链接游戏界面的显示
    connect(game,&Game::backToBegin,this,[=](){
        this->show();
        game->hide();
    });

}

begin::~begin()
{

    delete ui;
    delete game;
}

void begin::on_begin_loginOut_button_clicked()
{
    emit backToLogin();
}


void begin::on_begin_startNewGame_Button_clicked()
{
    game->show();
    this->hide();
}

