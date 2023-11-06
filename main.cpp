#include "login.h"
#include <QDebug>
#include <QApplication>
#include "./userdata.h"
#include "./config.h"
int main(int argc, char *argv[])
{
    userData user("txdnajflkb","123");
    user.writeInDataBase();
    qDebug()<<userData::findUser("tx");

    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}
