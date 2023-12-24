#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include "config.h"
namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
    // 配置数据结构体
    // 写入文件
    static void writeSettingDataToFolder(settingData *,QString path);
    // 文件读入
    static settingData *readSettingDataFromFolder(QString path);
    static void debugSettingData(settingData*);
private slots:
    // 确认修改
    void on_setting_confirmsetting_button_clicked();

    // 恢复修改前
    void on_setting_restoreModify_button_clicked();

    void on_setting_restoreDefault_button_clicked();

    void on_up_wall_clicked();

    void on_right_wall_clicked();

    void on_left_wall_clicked();

    void on_down_wall_clicked();

private:
    Ui::Setting *ui;

//    struct settingData{
//        int gameDifficult = 1;
//        int foodCount = 1;
//        int randSeed = 0;
//        double foodGenerationPro = .5;

//        int mapWidth = 10;
//        int mapHeight = 10;
//        bool upwall = true;
//        bool downwall = true;
//        bool leftwall = true;
//        bool rightwall = true;
//        int blockContinuous = 1;
//        int blockCount = 0;
//    }

    settingData *setting = new settingData();
    //  从ui组件读取值
    void readSettingDataFromInput(settingData*);
public:
    // 将值写入组件
    void writeSettingDataToComponent(settingData*);

signals:
    void toStartGame();
    void emitSettingData(settingData *);
};

#endif // SETTING_H
