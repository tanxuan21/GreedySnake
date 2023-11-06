#include "userdata.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include "./config.h"
#include <QtMath>
#include <qrandom.h>
#include <QTextStream>
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
        qDebug()<<"用户已存在";
        return 0;
    }
    QFile userDataBase(QString(projectPath)+"/data/demo.txt");
    userDataBase.open(QIODevice::Append);
    QTextStream writeStream(&userDataBase);
    writeStream<<this->username<<Qt::endl<<this->password<<Qt::endl;
    userDataBase.close();
    return 1;
}

userData *userData::findUser(const QString &username)
{
    QFile userDataBase(QString(projectPath)+"/data/demo.txt");
    userData *user = NULL;
    userDataBase.open(QIODevice::ReadOnly);
    while (!userDataBase.atEnd()) {
        QString usernameFromDataBase = userDataBase.readLine();
        usernameFromDataBase = usernameFromDataBase.chopped(1);// 删掉结尾的\n
        if(usernameFromDataBase == username){
            user = new userData(usernameFromDataBase,QString(userDataBase.readLine()));
            qDebug()<<"找到了!";
            break;
        }
    }
    return user;
}
