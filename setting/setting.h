#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

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
    struct setting{

    };
private slots:
    void on_setting_confirmsetting_button_clicked();

private:
    Ui::Setting *ui;
signals:
    void toStartGame();
};

#endif // SETTING_H
