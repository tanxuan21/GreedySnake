#include "gamemap.h"
#include <QPainter>
gameMap::gameMap(QWidget *parent)
    : QWidget{parent}
{

}

void gameMap::paintEvent(QPaintEvent *)
{
QPainter painter = QPainter(this);
painter.setBrush(Qt::white);
painter.drawRect(0,0,this->width(),this->height());
}
