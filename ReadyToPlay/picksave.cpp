#include "picksave.h"
#include "ui_picksave.h"
#include "./saveitem.h"
pickSave::pickSave(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pickSave)
{
    ui->setupUi(this);

    for(int i = 0;i<20;i++){
        saveItem *s = new saveItem();
        // 对item进行一些初始化操作
        s->setMapID(i);
        s->setMinimumHeight(20);

        // 列表容器
        QListWidgetItem *item = new QListWidgetItem();

        item->setSizeHint(QSize(100,80));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,s);

        // 绑定
        connect(s,&saveItem::continuePaly,this,[=](int MapId){
            emit continuePaly(MapId);
        });
        connect(s,&saveItem::review,this,[=](int MapId){
            emit review(MapId);
        });
        connect(s,&saveItem::deleteMap,this,[=](int MapId){
            emit deleteMap(MapId);
//            ui->listWidget->takeItem(MapId);
            // 删除列表有点问题
        });
        connect(s,&saveItem::reSet,this,[=](int MapId){
            emit reSet(MapId);
        });



    }
}

pickSave::~pickSave()
{
    delete ui;
}

void pickSave::on_pickSave_back_button_clicked()
{
    emit backToBegin();
}

