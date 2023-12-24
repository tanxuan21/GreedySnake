#include "setting.h"
#include "ui_setting.h"
#include "config.h"
#include <QFile>
#include <QLineEdit>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

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

    ui->food_generation_pro_1->setText("1分食物生成概率/%");
    ui->food_generation_pro_1->setMax(100);
    ui->food_generation_pro_1->setMin(1);

    ui->food_generation_pro_2->setText("2分食物生成概率/%");
    ui->food_generation_pro_2->setMax(100);
    ui->food_generation_pro_2->setMin(1);

    ui->food_generation_pro_3->setText("3分食物生成概率/%");
    ui->food_generation_pro_3->setMax(100);
    ui->food_generation_pro_3->setMin(1);


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

    emit saveGameNameChanged(saveGameName);


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
    <<Qt::endl<<setting->food_1_GenerationPro
    <<Qt::endl<<setting->food_2_GenerationPro
    <<Qt::endl<<setting->food_3_GenerationPro
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
    >>setting->food_1_GenerationPro
    >>setting->food_2_GenerationPro
    >>setting->food_3_GenerationPro
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
    <<setting->food_1_GenerationPro
    <<setting->food_2_GenerationPro
    <<setting->food_3_GenerationPro
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

//保存游戏和地图配置的四个函数//
void Setting::on_saveGameButton_clicked()
{
    QDir().mkpath("config"); // 创建目录

    // 获取输入内容作为文件名
    QString fileName = ui->saveGameText->text();

    // 检查文件名是否为空
    if (fileName.isEmpty())
    {
        qDebug() << "File name is empty!";
        return;
    }

    // 构建文件路径
    QString filePath = "config/" + fileName + ".config";


    // 从输入框中读取设置数据
    readSettingDataFromInput(setting);

    // 打开文件以写入数据
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // 创建一个文本流，用于写入数据
        QTextStream out(&file);

        // 逐行写入数据
        out << setting->gameDifficult << "\n"
            << setting->foodCount << "\n"
            << setting->randSeed << "\n"
            << setting->food_1_GenerationPro << " "
            << setting->food_2_GenerationPro << " "
            << setting->food_3_GenerationPro;

        // 关闭文件
        file.close();

        qDebug() << "Settings saved to file: " << filePath;
    }
    else
    {
        qDebug() << "Failed to open file for writing: " << filePath;
    }

}
void Setting::on_readGameButton_clicked()
{
    // 打开文件选择对话框，让用户选择配置文件
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Configuration File"), "config", tr("Config Files (*.config);;All Files (*)"));
    saveGameName = ui->readGameText->text();

    if (!filePath.isEmpty())
    {
        // 打开文件以读取数据
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //文本流，用于读取数据
            QTextStream in(&file);

            // 逐行读取数据
            in >> setting->gameDifficult
                >> setting->foodCount
                >> setting->randSeed
                >> setting->food_1_GenerationPro
                >> setting->food_2_GenerationPro
                >> setting->food_3_GenerationPro;

            writeSettingDataToComponent(setting);



            // 关闭文件
            file.close();

            qDebug() << "Settings loaded from file: " << filePath;
        }
        else
        {
            qDebug() << "Failed to open file for reading: " << filePath;
        }
    }
}
QString Setting::getSaveGameName() const {
    return saveGameName;
}
void Setting::on_saveMapButton_clicked()
{
    Setting::debugSettingData(this->setting);
    QDir().mkpath("map"); // 创建目录

    // 获取输入内容作为文件名
    QString fileName = ui->saveMapText->text();

    // 检查文件名是否为空
    if (fileName.isEmpty())
    {
        qDebug() << "File name is empty!";
        return;
    }

    // 构建文件路径
    QString filePath = "map/" + fileName + ".map";

    // 创建一个 settingData 对象


    // 从输入框中读取设置数据
    readSettingDataFromInput(setting);

    // 打开文件以写入数据
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // 创建一个文本流，用于写入数据
        QTextStream out(&file);
        // 将 settingData 对象的数据写入文件
        out <<setting->mapHeight << " "
            <<setting->mapWidth << "\n"
            <<setting->blockContinuous << " "
            <<setting->blockCount<< "\n"
            <<setting->upwall<< " "
            <<setting->downwall << " "
            <<setting->leftwall<< " "
            <<setting->rightwall<< " ";

        // 关闭文件
        file.close();

        qDebug() << "Settings saved to file: " << filePath;
    }
    else
    {
        qDebug() << "Failed to open file for writing: " << filePath;
    }


}
void Setting::on_readMapButton_clicked()
{
    // 打开文件选择对话框，让用户选择配置文件
    // 获取 readMapText 的输入内容作为文件名
    QString fileName = ui->readMapText->text();

    if (fileName.isEmpty())
    {
        qDebug() << "File name is empty!";
        return;
    }

    // 设置默认后缀和预选中的文件名
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDefaultSuffix("map");
    dialog.selectFile(fileName);

    // 打开文件选择对话框，让用户选择配置文件
    QString filePath;
    if (dialog.exec())
    {
        QStringList selectedFiles = dialog.selectedFiles();
        if (!selectedFiles.isEmpty())
        {
            filePath = selectedFiles.first();

            // 检查文件是否存在
            QFileInfo fileInfo(filePath);
            if (fileInfo.exists())
            {
                qDebug() << "File found: " << filePath;
                // 这里可以添加文件存在时的处理逻辑
                QMessageBox::information(this, tr("Success"), tr("File found and loaded successfully!"));
            }
            else
            {
                qDebug() << "File not found: " << filePath;
                // 这里可以添加文件不存在时的处理逻辑
                QMessageBox::warning(this, tr("Failure"), tr("File not found. Please try again."));
            }
        }
    }

    if (!filePath.isEmpty())
    {
        // 打开文件以读取数据
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            // 创建一个文本流，用于读取数据
            QTextStream in(&file);

            // 逐行读取数据
            in >> setting->mapHeight
                >> setting->mapWidth
                >> setting->blockContinuous
                >> setting->blockCount
                >> setting->upwall
                >> setting->downwall
                >> setting->leftwall
                >> setting->rightwall;

            // 在你的应用程序中应用这些设置
            writeSettingDataToComponent(setting);

            // 关闭文件
            file.close();

            qDebug() << "Settings loaded from file: " << filePath;
        }
        else
        {
            qDebug() << "Failed to open file for reading: " << filePath;
        }
    }
}

// 从input组件读进结构体
void Setting::readSettingDataFromInput(settingData *setting)
{
    setting->gameDifficult =  ui->game_difficult->getValue();
    setting->foodCount = ui->food_count->getValue();
    setting->randSeed = ui->randSeed->getValue();
    setting->food_1_GenerationPro = double(ui->food_generation_pro_1->getValue())/100;
    setting->food_2_GenerationPro = double(ui->food_generation_pro_2->getValue())/100;
    setting->food_3_GenerationPro = double(ui->food_generation_pro_3->getValue())/100;
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
    ui->food_generation_pro_1->MysetValue(setting->food_1_GenerationPro*100);
    ui->food_generation_pro_2->MysetValue(setting->food_2_GenerationPro*100);
    ui->food_generation_pro_3->MysetValue(setting->food_3_GenerationPro*100);
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

