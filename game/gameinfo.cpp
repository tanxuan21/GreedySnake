#include "gameinfo.h"
#include "ui_gameinfo.h"
#include <QPainter>
gameInfo::gameInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameInfo)
{
    ui->setupUi(this);

}

gameInfo::~gameInfo()
{
    delete ui;
}

void gameInfo::setText(QString text)
{
    ui->label->setText(text);
}

void gameInfo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QColor(200,200,200,230));
    painter.drawRect(0, 0, this->width(), this->height());
}

void gameInfo::on_save_quit_button_clicked()
{
    emit save_and_quit();
}


void gameInfo::on_continueGame_button_clicked()
{
    emit continueGame();
}


void gameInfo::on_restart_button_clicked()
{
    emit reStart();
}


void gameInfo::on_exit_button_clicked()
{
    emit exit();
}

