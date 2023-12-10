#include "setting.h"
#include "ui_setting.h"
#include "config.h"
#include <QFile>
Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    // 设置输入组件文本
    ui->game_difficult->setText("游戏难度");
    ui->game_difficult->setMax(10);
    ui->game_difficult->setMin(1);
    ui->food_count->setText("食物量");
    ui->food_count->setMax(5);
    ui->food_count->setMin(1);
    ui->food_generation_pro->setText("食物生成概率");
    ui->food_generation_pro->setMax(100);
    ui->food_generation_pro->setMin(1);

    ui->randSeed->setText("随机种子");
    ui->randSeed->setMax(1000000);

    ui->block_continuous->setText("障碍物最大连续");
    ui->block_continuous->setMax(10);
    ui->block_continuous->setMin(1);
    ui->block_count->setMax(15);
    ui->block_count->setMin(0);
    ui->block_count->setText("障碍物数量");


    ui->map_height->setText("地图高度");
    ui->map_height->setMax(20);
    ui->map_height->setMin(8);
    ui->map_width->setMax(20);
    ui->map_width->setMin(8);
    ui->map_width->setText("地图宽度");



    writeSettingDataToComponent(this->setting);


}

Setting::~Setting()
{
    delete ui;
}

void Setting::writeSettingDataToFolder(settingData *setting, QString path)
{
    QFile settingFile(path);
    settingFile.open(QIODevice::WriteOnly);
    QTextStream tx(&settingFile);
    tx<<setting->gameDifficult<<Qt::endl
    <<setting->foodCount <<Qt::endl
    <<setting->randSeed
    <<Qt::endl<<setting->foodGenerationPro
    <<Qt::endl<<setting->mapHeight
    <<Qt::endl<<setting->mapWidth
    <<Qt::endl<<setting->blockContinuous
    <<Qt::endl<<setting->blockCount
    <<Qt::endl
    <<setting->upwall<<" "
    <<setting->downwall<<" "
    <<setting->leftwall<<" "
    <<setting->rightwall<<" ";
    settingFile.close();
}

settingData *Setting::readSettingDataFromFolder(QString path)
{
    QFile settingFile(path);
    qDebug()<<"打开:"<<settingFile.open(QIODevice::ReadOnly);
    QTextStream tx(&settingFile);
    settingData *setting = new settingData();
    tx
    >>setting->gameDifficult
    >>setting->foodCount
    >>setting->randSeed
    >>setting->foodGenerationPro
    >>setting->mapHeight
    >>setting->mapWidth
    >>setting->blockContinuous
    >>setting->blockCount
    >>setting->upwall
    >>setting->downwall
    >>setting->leftwall
    >>setting->rightwall;
    settingFile.close();
    return setting;
}

void Setting::debugSettingData(settingData *setting)
{
    qDebug()
    <<setting->gameDifficult
    <<setting->foodCount
    <<setting->randSeed
    <<setting->foodGenerationPro
    <<setting->mapHeight
    <<setting->mapWidth
    <<setting->blockContinuous
    <<setting->blockCount
    <<setting->upwall
    <<setting->downwall
    <<setting->leftwall
    <<setting->rightwall;
}

void Setting::on_setting_confirmsetting_button_clicked()
{
    readSettingDataFromInput(this->setting);// 读进来
    emit emitSettingData(this->setting);// 射出去
    emit toStartGame();// 回到开始
}


// 从input组件读进结构体
void Setting::readSettingDataFromInput(settingData *setting)
{
    setting->gameDifficult =  ui->game_difficult->getValue();
    setting->foodCount = ui->food_count->getValue();
    setting->randSeed = ui->randSeed->getValue();
    setting->foodGenerationPro = double(ui->food_generation_pro->getValue())/100;
    setting->mapHeight = ui->map_height->getValue();
    setting->mapWidth = ui->map_width->getValue();
    setting->blockContinuous = ui->block_continuous->getValue();
    setting->blockCount = ui->block_count->getValue();
}

// 用设置结构体的数据设置输入组件的值
void Setting::writeSettingDataToComponent(settingData *setting)
{
    ui->game_difficult->MysetValue(setting->gameDifficult);
    ui->food_count->MysetValue(setting->foodCount);
    ui->randSeed->MysetValue(setting->randSeed);
    ui->food_generation_pro->MysetValue(setting->foodGenerationPro*100);
    ui->map_height->MysetValue(setting->mapHeight);
    ui->map_width->MysetValue(setting->mapWidth);
    ui->block_continuous->MysetValue(setting->blockContinuous);
    ui->block_count->MysetValue(setting->blockCount);
    if(setting->upwall){// 给样式
        ui->up_wall->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    else{
        ui->up_wall->setStyleSheet("");
    }
    if(setting->leftwall){// 给样式
        ui->left_wall->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    else{
        ui->left_wall->setStyleSheet("");
    }
    if(setting->rightwall){// 给样式
        ui->right_wall->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    else{
        ui->right_wall->setStyleSheet("");
    }
    if(setting->downwall){// 给样式
        ui->down_wall->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    else{
        ui->down_wall->setStyleSheet("");
    }
}

//恢复更改前
void Setting::on_setting_restoreModify_button_clicked()
{
    writeSettingDataToComponent(this->setting);
}

// 恢复默认设置
void Setting::on_setting_restoreDefault_button_clicked()
{
    delete this->setting;
    this->setting = new settingData();
    this->writeSettingDataToComponent(this->setting);

}


void Setting::on_up_wall_clicked()
{
    this->setting->upwall = !this->setting->upwall;
    if(this->setting->upwall){// 给样式
        ui->up_wall->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    else{
        ui->up_wall->setStyleSheet("");
    }
}


void Setting::on_right_wall_clicked()
{
    this->setting->rightwall= !this->setting->rightwall;
    if(this->setting->rightwall){// 给样式
        ui->right_wall->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    else{
        ui->right_wall->setStyleSheet("");
    }
}


void Setting::on_left_wall_clicked()
{
    this->setting->leftwall= !this->setting->leftwall;
    if(this->setting->leftwall){// 给样式
        ui->left_wall->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    else{
        ui->left_wall->setStyleSheet("");
    }
}


void Setting::on_down_wall_clicked()
{
    this->setting->downwall= !this->setting->downwall;
    if(this->setting->downwall){// 给样式
        ui->down_wall->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    else{
        ui->down_wall->setStyleSheet("");
    }
}

