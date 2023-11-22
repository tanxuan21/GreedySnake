#ifndef SNAKEUNIT_H
#define SNAKEUNIT_H

#include <QWidget>
#include <QPainter>
class SnakeUnit : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeUnit(QWidget *parent = nullptr);
    void setSize(const int&);// 设置蛇单元的大小
signals:
private:
    int size = 10;
protected:
    void paintEvent(QPaintEvent *);
};


#endif // SNAKEUNIT_H
