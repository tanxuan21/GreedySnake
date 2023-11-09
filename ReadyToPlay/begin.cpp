#include "begin.h"
#include "ui_begin.h"
begin::begin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::begin)
{

    ui->setupUi(this);


}

begin::~begin()
{

    delete ui;

}


void begin::on_begin_setting_button_clicked()
{
    emit toSetting();
}


void begin::on_begin_loginOut_button_clicked()
{
    emit backToLogin();
}


void begin::on_begin_startNewGame_Button_clicked()
{
    emit newGame();
}


void begin::on_begin_startFromSave_button_clicked()
{
    emit startFromSave();
}

