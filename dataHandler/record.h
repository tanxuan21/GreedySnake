#ifndef RECORD_H
#define RECORD_H
#include "./map.h"
struct food
{
    short x;short y;
    short value;
    food() {}
};
struct frameData{// 每一帧数据
    snackBody sb;
    QList<food *> foodArr;
};

class Record
{
public:
    Record();
    ~Record();
    // 读入回放对象
    // record文件内的存储格式

    // 蛇头位置x 蛇头位置y 方向 食物坐标x 食物坐标y 分值...
    // 蛇头位置x 蛇头位置y 方向 食物坐标x 食物坐标y 分值...
    //...
    QList<frameData *> recData;//
    static Record* readrecord(QString path);// 从文件读取
    static void writeRecord(QString path,Record *);// 从文件写入
    static void debug(Record *rec);
private:

};

#endif // RECORD_H
