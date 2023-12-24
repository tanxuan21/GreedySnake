#include "gameinfo.h"
#include "ui_gameinfo.h"
#include <QPainter>
#include <QFile>

#include <QDir>

gameInfo::gameInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameInfo)
{
    ui->setupUi(this);

    connect(ui->record_button, &QPushButton::clicked, this, &gameInfo::on_record_button_clicked);

}

gameInfo::~gameInfo()
{
    delete ui;
}

void gameInfo::setText(QString text)
{
    ui->label->setText(text);
}

void gameInfo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QColor(200,200,200,230));
    painter.drawRect(0, 0, this->width(), this->height());
}

void gameInfo::on_save_quit_button_clicked()
{
    emit save_and_quit();
}


void gameInfo::on_continueGame_button_clicked()
{
    emit continueGame();
}


void gameInfo::on_restart_button_clicked()
{
    emit reStart();
}


void gameInfo::on_exit_button_clicked()
{
    emit exit();
}
void gameInfo::on_record_button_clicked()
{
    // 获取文本框中的文字
    QString newRecordName = ui->lineEdit->text();

    // 获取记录文件夹路径
    QString recordFolderPath = "record/";

    // 打开记录文件夹
    QDir recordDir(recordFolderPath);

    // 获取文件夹中的所有文件
    QStringList fileList = recordDir.entryList(QDir::Files);

    // 如果有文件
    if (!fileList.isEmpty())
    {
        // 获取文件信息并按修改时间排序
        QList<QFileInfo> fileInfoList;
        for (const QString &fileName : fileList)
        {
            fileInfoList.append(QFileInfo(recordDir.filePath(fileName)));
        }

        // 按修改时间排序
        std::sort(fileInfoList.begin(), fileInfoList.end(), [](const QFileInfo &a, const QFileInfo &b) {
            return a.lastModified() > b.lastModified();
        });

        // 获取最新的文件名
        QString latestFileName = fileInfoList.first().fileName();

        // 构建新的记录文件路径
        QString newPath = recordFolderPath + newRecordName + ".rec";
        QString oldPath = recordFolderPath + latestFileName;

        // 重命名文件
        if (QFile::rename(oldPath, newPath))
        {
            qDebug() << "Record file renamed successfully!";
            // 删除包含 "default" 的文件
            for (const QFileInfo &fileInfo : fileInfoList)
            {
                if (fileInfo.fileName().contains("default"))
                {
                    if (QFile::remove(fileInfo.filePath()))
                    {
                        qDebug() << "File removed successfully: " << fileInfo.fileName();
                    }
                    else
                    {
                        qDebug() << "Failed to remove file: " << fileInfo.fileName();
                    }
                }
            }

        }
        else
        {
            qDebug() << "Failed to rename record file!";
        }
    }
    else
    {
        qDebug() << "No record files found in the folder!";
    }
}

