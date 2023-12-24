#include "begin.h"
#include "ui_begin.h"
begin::begin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::begin)
{

    ui->setupUi(this);

}

void begin::setUser(userData * user)
{
    ui->begin_user_label->setText("用户名:"+user->getUsername());
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

void begin::on_look_record_button_clicked()
{
    emit lookGame();
}

