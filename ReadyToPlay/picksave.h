#ifndef PICKSAVE_H
#define PICKSAVE_H

#include <QWidget>
#include "dataHandler/userdata.h"
namespace Ui {
class pickSave;
}

class pickSave : public QWidget
{
    Q_OBJECT

public:
    explicit pickSave(QWidget *parent = nullptr);
    ~pickSave();
    void readMap(userData* user);// 读取的存档
private slots:
    void on_pickSave_back_button_clicked();

    void on_pickSave_refresh_button_clicked();

private:
    Ui::pickSave *ui;

signals:
    void backToBegin();

    void continuePaly(int);
    void review(int);
    void deleteMap(int);
    void reSet(int);
    void refreshMapList();
};

#endif // PICKSAVE_H
