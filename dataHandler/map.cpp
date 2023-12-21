#include "map.h"
#include <QFile>
Map::Map()
{

}

Map::~Map()
{

}
// 地图文件存储格式:
/*
 int int int
 int int int
 ...
 int int int
 -
 int int
 int int
 ...
 int int
 -
 int int
 int int
 ...
 int int
 -
 int int int
 -
 int int int
 -
*/
// 每个-结束一组.
//分别是:
//蛇身组 食物组 障碍物组 蛇头组 蛇尾组
Map *Map::LoadMap(QString path)
{
    QFile file(path);
    Map *map = new Map();
    file.open(QIODevice::ReadOnly);
    QTextStream read(&file);
    int groupNum = 1;
    while(!read.atEnd()){
        QStringList l = read.readLine().split(' ');

        if(l[0]=="-"){
            //qDebug()<<"-";
            groupNum++;
            continue;
        }
        else{
            if(groupNum == 1){
                snackBody snackbd;
                snackbd.x = l[0].toInt();
                snackbd.y = l[1].toInt();
                snackbd.dir = l[2].toInt();
                map->snack.push_back(snackbd);
            }
            else if(groupNum == 2){
                QPoint p;
                p.rx() = l[0].toInt();
                p.ry() = l[1].toInt();
                map->foodArry.push_back(p);
            }
            else if(groupNum == 3){
                QPoint p;
                p.rx() = l[0].toInt();
                p.ry() = l[1].toInt();
                map->blockArry.push_back(p);
            }
            else if(groupNum == 4){
                snackBody snackbd;
                snackbd.x = l[0].toInt();
                snackbd.y = l[1].toInt();
                snackbd.dir = l[2].toInt();
                map->snackHead = snackbd;
            }
            else if(groupNum == 5){
                snackBody snackbd;
                snackbd.x = l[0].toInt();
                snackbd.y = l[1].toInt();
                snackbd.dir = l[2].toInt();
                map->snackTail = snackbd;
            }
        }
    }
    return map;
}

Map *Map::createMap(settingData *s)
{
    Map *map = new Map();
    // 生成障碍物.包括后期面所有直接从setting写入的代码也都要更改为从map里写入.
    return map;
}

void Map::writeMap(QList<gameProps *> &snack, QList<gameProps*> &foodArry, QList<gameProps*> &blockArry, gameProps *snackHead, gameProps *snackTail, QString path)
{
    QFile map(path);
    map.open(QIODevice::WriteOnly);
    QTextStream tx(&map);
    // 蛇身
    for(int i = 0;i<snack.length();i++){
        tx<<snack[i]->getPoint().x()<<" "<<snack[i]->getPoint().y()<<" "<<snack[i]->getDirection()<<Qt::endl;
    }
    tx<<'-'<<Qt::endl;
    // 食物
    for(int i = 0;i<foodArry.length();i++){
        tx<<foodArry[i]->getPoint().x()<<" "<<foodArry[i]->getPoint().y()<<" "<<Qt::endl;
    }
    tx<<'-'<<Qt::endl;
    // 障碍物
    for(int i = 0;i<blockArry.length();i++){
        tx<<blockArry[i]->getPoint().x()<<" "<<blockArry[i]->getPoint().y()<<" "<<Qt::endl;
    }
    tx<<'-'<<Qt::endl;
    // 蛇头
    tx<<snackHead->getPoint().x()<<" "<<snackHead->getPoint().y()<<" "<<snackHead->getDirection()<<Qt::endl;
    tx<<'-'<<Qt::endl;
    // 蛇尾
    tx<<snackTail->getPoint().x()<<" "<<snackTail->getPoint().y()<<" "<<snackTail->getDirection()<<Qt::endl;
    tx<<'-'<<Qt::endl;
}

void Map::debug()
{
    qDebug()<<"蛇身";
    for(int i = 0;i<snack.length();i++){
        qDebug()<<snack[i].x<<snack[i].y<<snack[i].dir;
    }
    qDebug()<<"食物";
    for(int i = 0;i<foodArry.length();i++){
        qDebug()<<foodArry[i].x()<<foodArry[i].y();
    }
    qDebug()<<"障碍物";
    for(int i = 0;i<blockArry.length();i++){
        qDebug()<<blockArry[i].x()<<blockArry[i].y();
    }
    qDebug()<<"蛇头";
    qDebug()<<snackHead.x<<snackHead.y<<snackHead.dir;
    qDebug()<<"蛇尾";
    qDebug()<<snackTail.x<<snackTail.y<<snackTail.dir;
}
