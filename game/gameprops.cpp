#include "gameprops.h"
#include "ui_gameprops.h"
#include <QPainter>
gameProps::gameProps(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameProps)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

gameProps::~gameProps()
{
    delete ui;
}

gameProps::gameProps(gameProps *p,QWidget *parent):
    QWidget(parent),
    ui(new Ui::gameProps)
{
    this->color = p->color;
    this->pos() = p->pos();
    this->direction = p->direction;
    this->size = p->size;

}

void gameProps::setSize(const int &s)
{
    this->size = s;
    this->resize(this->size,this->size);
}

void gameProps::setPos(const QPoint &pos)
{
    this->gamePos = pos;
}

void gameProps::setDirection(int keyID)
{
    this->direction = keyID;
}

int gameProps::getDirection()
{
    return this->direction;
}

QPoint gameProps::getPoint()
{
    return this->gamePos;
}

void gameProps::setColor(QColor color)
{
    this->color = color;
}

void gameProps::paintEvent(QPaintEvent *)
{
    QPainter painter = QPainter(this);
    painter.setBrush(this->color);
    painter.drawRect(0,0,this->width(),this->height());
}
