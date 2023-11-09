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
