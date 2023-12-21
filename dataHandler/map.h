#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "../setting/setting.h"
#include "../game/gameprops.h"
struct snackBody{
    int x;
    int y;
    int dir;
    snackBody(int x,int y,int dir){
        this->x = x;
        this->y = y;
        this->dir = dir;
    }
    snackBody(){}
};
class Map
{
public:
    Map();
    ~Map();
    static Map* LoadMap(QString path);// 通过文件存档创建地图,返回地图对象.路径只要给到地图号即可.
    static Map *createMap(settingData *s);//通过设置对象构造地图,返回地图对象
    void writeMap( QList<gameProps *> &snack, QList<gameProps *> &foodArry,
               QList<gameProps *> &blockArry, gameProps* snackHead,
                gameProps *snackTail,QString path);// 把所有对象都给它然后保存成文件.
    void debug();

    // 地图大小
    struct mapSize{
        int width = 10;
        int height = 10;
    };
    // 墙的虚实
    struct wall{
        bool up = false;
        bool down  =false;
        bool left = false;
        bool right = false;
    };
    // 障碍物坐标
    QList<QPoint> blockArry;
    // 蛇
    QList<snackBody> snack;
    // 食物
    QList<QPoint> foodArry;
    snackBody snackHead;
    snackBody snackTail;

};

#endif // MAPLOADER_H
