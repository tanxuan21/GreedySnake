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
        s->setMinimumHeight(20);
        QListWidgetItem *item = new QListWidgetItem();

        item->setSizeHint(QSize(100,80));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,s);
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

