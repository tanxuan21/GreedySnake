#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include "config.h"
#include "map.h"
#include "record.h"
// 用户名数据处理
class userData
{
public:
    userData(const QString &username,const QString &password);
    int writeInDataBase();// 将用户数据写入数据库,返回1成功,0用户存在,-1系统错误
    static userData* findUser(const QString &username);// 在数据库查找用户.返回一个用户对象指针
    // 用户名getter
    QString getUsername(){
        return username;
    }
    // 密码getter
    QString getpassword(){
        return password;
    }
    QString getPath();
    // 读取用户保存的地图,返回地图ID QStringList
    QStringList readuserMapFolder();
    // 删除地图 ,返回是否删除成功.(不成功能让你怎么样吗...)
    bool deleteuserMapFolder(int MapID);
    // 创建新地图返回新地图文件夹ID.
    int createNewMapFolder();
    // 保存地图,传递:地图对象,配置对象,地图ID,
    bool saveMap(const int &MapID,Map* map, settingData *settingdata,Record *record);

    // 读进设置对象
    void readSettingData(settingData *);
    // 写入设置对象
    void writeSettingData(QString path,settingData *);

    // 读入地图对象
    Map* readMap(QString path);
    // 根据设置创建地图
    Map* createMap(settingData *);
    // 写入地图
    void writeMap(QString path,Map *map);

    // 读入回放对象
    Record* readrecord(QString path);
    void writeRecord(QString path,Record *);

    //保存时间
    void writeTime(QString path,QString time);
    // 读出时间
    QString readTime(QString path);
private:
    // 用户名,密码
    QString username;
    QString password;
};

#endif // USERDATA_H
