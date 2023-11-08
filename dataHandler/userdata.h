#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
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
private:
    // 用户名,密码
    QString username;
    QString password;
};

#endif // USERDATA_H
