#include "demo.h"
#include "ui_demo.h"

Demo::Demo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Demo)
{
    ui->setupUi(this);
}

Demo::~Demo()
{
    delete ui;
}

void Demo::on_pushButton_clicked()
{
    qDebug()<<ui->widget->getValue();
    qDebug()<<ui->widget_2->getValue();
    qDebug()<<ui->widget_3->getValue();
}

