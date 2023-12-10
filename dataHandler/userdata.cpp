#include "userdata.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include "./config.h"
#include <QTextStream>
#include "setting/setting.h"
userData::userData(const QString &username,const QString &password)
{
this->username = username;
this->password = password;

}

int userData::writeInDataBase()
{
// 当前路径exec文件的绝对路径
//    QDir dir;
//    QString currentPath = dir.currentPath();
//    qDebug()<<currentPath;
    // 找到了用户就返回错误
    if(userData::findUser(this->username)){
        return 0;
    }
    QFile userDataBase(QString(projectPath)+"/data/user.txt");
    userDataBase.open(QIODevice::Append);
    QTextStream writeStream(&userDataBase);
    writeStream<<this->username<<Qt::endl<<this->password<<Qt::endl;
    userDataBase.close();
    return 1;
}

userData *userData::findUser(const QString &username)
{
    QFile userDataBase(QString(projectPath)+"/data/user.txt");
    userData *user = NULL;
    userDataBase.open(QIODevice::ReadOnly);
    while (!userDataBase.atEnd()) {
        QString usernameFromDataBase = userDataBase.readLine();
        usernameFromDataBase = usernameFromDataBase.chopped(1);// 删掉结尾的\n
        if(usernameFromDataBase == username){
            QString userpasswordFromDataBase = userDataBase.readLine();
            userpasswordFromDataBase = userpasswordFromDataBase.chopped(1);
            user = new userData(usernameFromDataBase,userpasswordFromDataBase);
            break;
        }
    }
    return user;
}

QString userData::getPath()
{
    return QString(projectPath) + "data/game/"+this->username;
}

QStringList userData::readuserMapFolder()
{
    QString Mappath = QString(projectPath) + "data/game/"+this->username;// 这个路径的子文件夹就是地图数据.全部读出来看看
    QDir userMapDataBase(Mappath);
    QStringList ls = userMapDataBase.entryList();
    ls.removeOne(".");
    ls.removeOne("..");
    return ls;
}

bool userData::deleteuserMapFolder(int MapID)
{
    QString path = QString(projectPath)+"data/game/"+this->username+"/"+QString::number(MapID);
    return QDir(path).removeRecursively();
}

int userData::createNewMapFolder()
{
    QString gameMapPath = QString(projectPath) + "data/game/"+this->username+"/";

    for(int i = 0;;i++){
        qDebug()<<gameMapPath+QString::number(i);
        if(!(QDir().exists(gameMapPath+QString::number(i)))){// 不存在就创建.然后退出循环.
            qDebug()<<QDir().mkpath(gameMapPath+QString::number(i));
            return i;
        }
    }
}

bool userData::saveMap(const int &MapID, Map *map, settingData *settingdata, Record *record)
{
    // 只是缺后缀
    QString path = QString(projectPath)+"data/game/"+this->username+"/"+QString::number(MapID)+"/"+username;
    writeMap(path+".map",map);
    writeRecord(path+".rec",record);
    writeSettingData(path+".config",settingdata);
    QDateTime now = QDateTime::currentDateTime();
    QString time = now.toString("yyyy-MM-dd HH:mm:ss");
    writeTime(path+".time",time);
    return true;
}

void userData::writeSettingData(QString path,settingData *settingData)
{
   Setting::writeSettingDataToFolder(settingData,path);
}

Map* userData::readMap(QString path)
{
    return Map::LoadMap(path);
}

Map* userData::createMap(settingData *s)
{
    return Map::createMap(s);
}

void userData::writeMap(QString path,Map *map)
{

}

Record *userData::readrecord(QString path)
{
    return Record::readrecord(path);
}

void userData::writeRecord(QString path, Record *)
{

}

void userData::writeTime(QString path,QString time)
{
    QFile userDataBase(path);
    userDataBase.open(QIODevice::WriteOnly);
    QTextStream writeStream(&userDataBase);
    writeStream<<time;
    userDataBase.close();
}

QString userData::readTime(QString path)
{
    QFile userDataBase(path);
    userDataBase.open(QIODevice::ReadOnly);
    QTextStream readStream(&userDataBase);
    QString time,t_;
    readStream>>time;
    readStream>>t_;
    userDataBase.close();
    return time+" "+t_;
}
