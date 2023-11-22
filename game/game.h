#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "./snakeunit.h"
#include <QQueue>
#include <QTimer>
namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Game *ui;
    SnakeUnit *snackU;


    QQueue<SnakeUnit> snack;
    // 游戏时钟
    QTimer *timer;
    bool IsPause = true;
    void switchPause(){
        IsPause = !IsPause;
        if(IsPause){timer->start();}
        else{timer->stop();}
    }
    void update();// 游戏每帧调用
signals:
    void backToBegin();
protected:
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent*);
};

#endif // GAME_H
