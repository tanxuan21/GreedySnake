#include "gamemap.h"
#include <QPainter>
gameMap::gameMap(QWidget *parent)
    : QWidget{parent}
{

}

void gameMap::setSize(int size)
{
    this->unitSize = size;

}

void gameMap::paintEvent(QPaintEvent *)
{
    QPainter painter = QPainter(this);
    painter.setBrush(Qt::white);
    painter.drawRect(0,0,this->width(),this->height());

    for(int i = 0;i<this->height();i+=this->unitSize){
        painter.drawLine(QPoint(0,i),QPoint(this->width(),i));

    }
    for(int i = 0;i<this->width();i+=this->unitSize){
        painter.drawLine(QPoint(i,0),QPoint(i,this->height()));

    }

}
