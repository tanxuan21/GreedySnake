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

void saveItem::setImgTest(QString s)
{

    ui->saveItem_gameImg_label->setText(s);

}

void saveItem::setImg(QPixmap img)
{

    //    img = img.scaled(ui->saveItem_gameImg_label->width()*2, ui->saveItem_gameImg_label->height()*2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //    ui->saveItem_gameImg_label->setScaledContents(true);// 撑满label
    img = img.scaled(ui->saveItem_gameImg_label->width(),ui->saveItem_gameImg_label->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    ui->saveItem_gameImg_label->setPixmap(img);
    ui->saveItem_gameImg_label->setAlignment(Qt::AlignCenter);
}


void saveItem::setLastTime(QString s)
{
    ui->saveItem_lastTime_label->setText(s);
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

