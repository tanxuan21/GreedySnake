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

    // 绘制边框
    // if (setting) {
    //     QPen borderPen;
    //     if (setting->upwall) {
    //         borderPen.setColor(QColor(230, 6, 45)); // 红色
    //         qDebug() << "Red Border Received!";
    //     } else {
    //         borderPen.setColor(QColor(184, 192, 104)); // 绿色
    //         qDebug() << "Green Border Received!";
    //     }
    //     borderPen.setWidth(2); // 边框宽度
    //     painter.setPen(borderPen);
    //     painter.drawRect(0, 0, this->width(), this->height());
    // }





    painter.setBrush(Qt::black);
    painter.drawRect(0,0,this->width(),this->height());


    painter.setPen(QPen(QColor(Qt::red), 10));/*
    // 绘制红线
    painter.drawLine(QPoint(0, 0), QPoint(this->width(), 0));
    painter.drawLine(QPoint(0, this->height()), QPoint(this->width(), this->height()));
    painter.drawLine(QPoint(0, 0), QPoint(0, this->height()));
    painter.drawLine(QPoint(this->width(), 0), QPoint(this->width(), this->height()));*/

    // painter.setPen(QPen(QColor(Qt::black), 0));
    // for(int i = 1;i<this->height()-1;i+=this->unitSize){
    //     painter.drawLine(QPoint(0,i),QPoint(this->width(),i));
    // }
    // for(int i = 1;i<this->width()-1;i+=this->unitSize){
    //     painter.drawLine(QPoint(i,0),QPoint(i,this->height()));
    // }

}
