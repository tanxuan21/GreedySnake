#include "registerwidget.h"
#include "ui_registerwidget.h"

registerWidget::registerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
}

registerWidget::~registerWidget()
{
    delete ui;
}

void registerWidget::on_register_back_Button_clicked()
{
    emit backToLogin();
    this->hide();
}


void registerWidget::on_register_confirm_Button_clicked()
{
    emit registed_and_Login();
    // 确认注册

    this->hide();
}

