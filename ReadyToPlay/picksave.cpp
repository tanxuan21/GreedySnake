#include "picksave.h"
#include "ui_picksave.h"
#include "./saveitem.h"
#include "config.h"
#include <QDir>
#include <QDirIterator>
#include "dataHandler/userdata.h"
pickSave::pickSave(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pickSave)
{
    ui->setupUi(this);


}

pickSave::~pickSave()
{
    delete ui;
}

void pickSave::on_pickSave_back_button_clicked()
{
    emit backToBegin();
}

void pickSave::readMap(userData * user)
{

//    QString Mappath = QString(projectPath) + "data/game/"+username;// 这个路径的子文件夹就是地图数据.全部读出来看看
//    QDir userMapDataBase(Mappath);
//    QStringList ls = userMapDataBase.entryList();
//    for(const QString& entry : ls) {
//        if(userMapDataBase.exists(entry)) {
//            qDebug() << entry.toInt();
//        }
//    }
//    QDirIterator it(userMapDataBase.path());
//    while (it.hasNext()) {
//        it.next();
//        QString f = it.filePath();
//        qDebug()<<f;
//    }


//    for(int i = 0;i<10;i++){
    // 读取存档
    ui->listWidget->clear();
    for(const QString& i:user->readuserMapFolder()){
        if(i=="."||i==".."){continue;}// 跳过没用的文件.
        saveItem *s = new saveItem();
        QString path = QString(projectPath) + "data/game/"+user->getUsername()+"/"+i+"/";
        // 对item进行一些初始化操作
        s->setMapID(i.toInt());
        s->setImgTest(i);
        s->setMinimumHeight(20);
        s->setLastTime(user->readTime(path+user->getUsername()+".time"));
        // 列表容器
        QListWidgetItem *item = new QListWidgetItem();

        item->setSizeHint(QSize(100,80));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,s);

        // 绑定

        // 继续游戏
        connect(s,&saveItem::continuePaly,this,[=](int MapId){
            emit continuePaly(MapId);
        });
        // 回放游戏
        connect(s,&saveItem::review,this,[=](int MapId){
            emit review(MapId);
        });
        // 删除地图
        connect(s,&saveItem::deleteMap,this,[=](int MapId){
            // 删除文件
            emit deleteMap(MapId);

            // 删除UI地图
            // 不是直接把ID当作下标来用的.要找的.
            for(int i = 0;i<ui->listWidget->count();i++){
                // 获取列表的ID.
                int id = ((saveItem*)(ui->listWidget->itemWidget(ui->listWidget->item(i))))->getMapID();
                if(id==MapId){
                    ui->listWidget->takeItem(i);
                    break;
                }

            }
        });
        // 重新设置游戏
        connect(s,&saveItem::reSet,this,[=](int MapId){
            emit reSet(MapId);
        });
    }

}

void pickSave::on_pickSave_refresh_button_clicked()
{
    emit refreshMapList();
}

