#include "saveitem.h"
#include "ui_saveitem.h"

saveItem::saveItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::saveItem)
{
    ui->setupUi(this);
}

saveItem::~saveItem()
{
    delete ui;
}

// 继续游戏
void saveItem::on_saveItem_continuePlay_button_clicked()
{
    emit continuePaly(this->MapID);
}

// 回放
void saveItem::on_saveItem_review_button_clicked()
{
    emit review(this->MapID);
}

// 删除地图
void saveItem::on_saveItem_delete_button_clicked()
{
    emit deleteMap(this->MapID);
}

// 重新设置
void saveItem::on_saveItem_reSet_button_clicked()
{
    emit reSet(this->MapID);
}

