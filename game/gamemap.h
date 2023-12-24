#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>

class gameMap : public QWidget
{
    Q_OBJECT
public:
    explicit gameMap(QWidget *parent = nullptr);
    void setSize(int size);


signals:
protected:
    void paintEvent(QPaintEvent*);
private:
    int unitSize = 50;
};

#endif // GAMEMAP_H
