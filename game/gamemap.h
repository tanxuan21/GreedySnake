#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>

class gameMap : public QWidget
{
    Q_OBJECT
public:
    explicit gameMap(QWidget *parent = nullptr);

signals:
protected:
    void paintEvent(QPaintEvent*);

};

#endif // GAMEMAP_H
