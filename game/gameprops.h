#ifndef GAMEPROPS_H
#define GAMEPROPS_H

#include <QWidget>

namespace Ui {
class gameProps;
}

class gameProps : public QWidget
{
    Q_OBJECT

public:
//    explicit gameProps(QWidget *parent = nullptr);
    gameProps(QWidget *parent = nullptr);
    ~gameProps();
    gameProps(gameProps *p,QWidget *parent);
    void setImg(QString path);
    void setColor(QColor color);
    void setSize(const int &s);
    void setPos(const QPoint& pos);
    void setDirection(int keyID);

    int getDirection();
    QPoint getPoint();

private:
    Ui::gameProps *ui;
    QColor color;
    int size = 10;
    QPoint gamePos;
    int direction = 0;// 记录方向.作为蛇单元的方向.
protected:
    void paintEvent(QPaintEvent * event);
};

#endif // GAMEPROPS_H
