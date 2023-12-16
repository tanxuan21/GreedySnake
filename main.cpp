#include "./LoginRegiste/login.h"
#include <QDebug>
#include <QApplication>
#include "./dataHandler/userdata.h"
#include "./config.h"
#include "setting/setting.h"
#include "./demo.h"
#include <QScreen>
#include <QDateTime>
int main(int argc, char *argv[])
{
//    userData user("txdnajflkb","123");
//    user.writeInDataBase();
//    qDebug()<<userData::findUser("tx");

//    settingData *s = Setting::readSettingDataFromFolder("/Users/tanxuan21/Desktop/homework/junior-high/Programming/GreedySnake/data/game/1/1/tx.txt");
//    Setting::debugSettingData(s);
//    s->gameDifficult = 123456;
//    Setting::writeSettingDataToFolder(s,"/Users/tanxuan21/Desktop/homework/junior-high/Programming/GreedySnake/data/game/1/1/adfh.txt");
    // 获取当前纪元时间

    // 队列操作
//    QQueue<int> qe;
//    for(int i = 0;i<5;i++){
//        qe.enqueue(i);
//    }
//    qe.enqueue(1234);
//    for(int i = 0;i<6;i++){
//        qDebug()<<qe[i];
//    }

    QApplication a(argc, argv);
    login w;
    // Demo w;
    w.show();

    //QScreen *s = w.screen();
    // 截图
//    QPixmap screenshot = w.grab();
//    screenshot.save("/Users/tanxuan21/Documents/screenCut/screenshot.png");

    return a.exec();
}
