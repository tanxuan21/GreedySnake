#ifndef BEGIN_H
#define BEGIN_H

#include <QWidget>
#include "dataHandler/userdata.h"
namespace Ui {
class begin;
}

class begin : public QWidget
{
    Q_OBJECT

public:
    explicit begin(QWidget *parent = nullptr);
    void setUser(userData *);
    ~begin();

private slots:
    void on_begin_setting_button_clicked();

    void on_begin_loginOut_button_clicked();

    void on_begin_startNewGame_Button_clicked();

    void on_begin_startFromSave_button_clicked();

private:
    userData *user;
    Ui::begin *ui;
signals:
    void toSetting();// 打开设置界面
    void backToLogin();// 返回登录界面
    void newGame();// 新游戏
    void startFromSave();// 存档选择界面
};

#endif // BEGIN_H
