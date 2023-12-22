#include "map.h"
#include <QFile>
#include "../tool/tool.h"
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
    // 蛇的初始化状态
    for(int i = 0;i<4;i++){
        map->snack.push_back(snackBody(s->mapWidth/2+i,s->mapHeight/2,Qt::Key_D));
    }
    map->snackHead = snackBody(s->mapWidth/2+4,s->mapHeight/2,Qt::Key_D);
    map->snackTail = snackBody(s->mapWidth/2,s->mapHeight/2,Qt::Key_D);

    // 障碍物
    qDebug()<<"生成障碍物"<<s->blockCount;
    for(int i = 0;i<s->blockCount;i++){
        QPoint blockP = QPoint(0,0);
        if(map->blockArry.length()==0){// 如果根本就没有任何障碍物,要先生成一个.
            do{
                blockP.rx() = tool::randomInt(0,s->mapWidth-1);
                blockP.ry() = tool::randomInt(0,s->mapHeight-1);
            }while(map->noAcceptBlockP(blockP,s));
            // 添加进障碍物数组
            map->blockArry.push_back(blockP);
            qDebug()<<"length0";
        }
        else if(tool::randomInt(0,10) <= s->blockContinuous){// 生成的随机数在连续性的范围之内
            int index = tool::randomInt(0,map->blockArry.length()-1);
            while(1){
                // 数组里随机挑选一个,再看它四周是否有重叠.
                // 检查四个方向的点位是否合法.
                blockP = map->blockArry[index];
                qDebug()<<"选中的点"<<blockP.x()<<blockP.y();

                int beginIndex = tool::randomInt(0,3);// 开始位置
                bool isFind = false;
                for(int i = 0;i<4;i++){
                    blockP = map->blockArry[index];
                    blockP = map->randomAround(blockP,beginIndex,i);// 绕四周找一找
                    if(!map->noAcceptBlockP(blockP,s)){// 可以接受,就放到数组里.
                        map->blockArry.push_back(blockP);
                        isFind = true;// 并且设置找到了.
                        break;
                    }
                    qDebug()<<"      周围的点"<<blockP.x()<<blockP.y();
                }
                if(!isFind){// 四个方向都不合法,顺着数组找下一个.
                    index = (index+1)%map->snack.length();// 防止越界
                }
                else{
                    break;
                }
            }
        }
        else{// 生成的随机数不在连续的范围之内,直接随机生成不重叠的即可.
            // 判读是否合法.也就是判断重叠
            do{
                blockP.rx() = tool::randomInt(0,s->mapWidth-1);
                blockP.ry() = tool::randomInt(0,s->mapHeight-1);
            }while(map->noAcceptBlockP(blockP,s));
            // 添加进障碍物数组
            map->blockArry.push_back(blockP);
        }
    }
    qDebug()<<"--------";
    for(int i = 0;i<map->blockArry.length();i++){
        qDebug()<<map->blockArry[i].x()<<map->blockArry[i].y();
    }
    qDebug()<<"--------";
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
