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
private:
    bool inOnSnackBody(const QPoint &p){
        for(int i = 0;i<snack.length();i++){
            if(p.x() == snack[i].x && p.y() == snack[i].y){
                return true;
            }
        }
        return false;
    }
    bool noAcceptBlockP(const QPoint &p,settingData *s){// 是否接受障碍物坐标?
        if(p.x() < 0 || p.x()>s->mapWidth-1 || p.y() < 0 || p.y() > s->mapHeight-1){// 超过地图范围也不接受
            return true;
        }
        return (blockArry.contains(p) || inOnSnackBody(p));// 有一个重叠就不接受
    }
    QPoint randomAround(const QPoint& blockP,int beginIndex,int offset){
        int fourDir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        int index = ((beginIndex % 4) + offset ) % 4;
        return QPoint(blockP.x()+fourDir[index][0],blockP.y()+fourDir[index][1]);
    }
};

#endif // MAPLOADER_H
