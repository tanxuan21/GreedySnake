#include "snakeunit.h"
#include <QPainter>
#include "QPushButton"
SnakeUnit::SnakeUnit(QWidget *parent)
    : QWidget{parent}
{
//    QPalette palette(this->palette());
//    palette.setColor(QPalette::Window, Qt::red);
//    this->setPalette(palette);

}

void SnakeUnit::setSize(const int &s)
{
    this->size = s;
    this->resize(this->size,this->size);
}

void SnakeUnit::paintEvent(QPaintEvent *)
{
    QPainter painter = QPainter(this);
    painter.setBrush(QColor(10,200,100));
    painter.drawRect(0,0,this->width(),this->height());
}
