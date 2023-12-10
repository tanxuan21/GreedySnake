#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QVector2D>
#include "../setting/setting.h"
class Map
{
public:
    Map();
    ~Map();
    static Map* LoadMap(QString path);// 通过文件存档创建地图,返回地图对象
    static Map *createMap(settingData *s);//通过设置对象构造地图,返回地图对象

private:
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
    // 障碍物
    QVector2D blockArry;
    // 蛇


};

#endif // MAPLOADER_H
