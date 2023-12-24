#include "record.h"
#include <QFile>
Record::Record()
{

}

Record::~Record()
{

}

Record *Record::readrecord(QString path)
{
    Record *rec = new Record();
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream read(&file);
    // 蛇头位置x 蛇头位置y 方向 食物坐标x 食物坐标y 分值...
    // 蛇头位置x 蛇头位置y 方向 食物坐标x 食物坐标y 分值...
    //...
    while(!read.atEnd()){
        frameData *fram = new frameData();

        QStringList l = read.readLine().split(' ');
        snackBody sb = snackBody();

        sb.x = l[0].toInt();
        sb.y = l[1].toInt();
        sb.dir = l[2].toInt();

        QList<food *> foodArr = QList<food *>();
        food *f ;
        for(int i = 3;i<l.length()-1;i+=3){
            f = new food();
            f->x = l[i].toInt();
            f->y = l[i+1].toInt();
            f->value = l[i+2].toInt();
            foodArr.push_back(f);
        }
        fram->sb = sb;
        fram->foodArr = foodArr;
        rec->recData.push_back(fram);
    }
    Record::debug(rec);
    return rec;
}

void Record::writeRecord(QString path, Record *rec)
{
    QFile recFile(path);
    recFile.open(QIODevice::WriteOnly);
    QTextStream tx(&recFile);

    for(int i = 0;i<rec->recData.length();i++){
        frameData *f = rec->recData[i];
        tx<<f->sb.x<<" "<<f->sb.y<<" "<<f->sb.dir<<" ";
        for(int j = 0;j<f->foodArr.length();j++){
            tx<<f->foodArr[j]->x<<" "<<f->foodArr[j]->y<<" "<<f->foodArr[j]->value<<" ";
        }
        tx<<Qt::endl;
    }
    return ;
}

void Record::debug(Record *rec)
{
    for(int i = 0;i<rec->recData.length();i++){
        frameData *f = rec->recData[i];
        qDebug()<<"蛇头"<<f->sb.x<<f->sb.y<<f->sb.dir;
        for(int j = 0;j<f->foodArr.length();j++){
            qDebug()<<f->foodArr[j]->x<<f->foodArr[j]->y<<f->foodArr[j]->value;
        }
        qDebug()<<"-----------------------";
    }
}
