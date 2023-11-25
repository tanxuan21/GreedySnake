#ifndef SAVEITEM_H
#define SAVEITEM_H

#include <QWidget>

namespace Ui {
class saveItem;
}

class saveItem : public QWidget
{
    Q_OBJECT

public:
    explicit saveItem(QWidget *parent = nullptr);
    ~saveItem();
    void init();
    void setMapID(int id){this->MapID = id;};
    int getMapID(){return this->MapID;};
    void setImgTest(QString);
private slots:
    void on_saveItem_continuePlay_button_clicked();
    void on_saveItem_review_button_clicked();
    void on_saveItem_delete_button_clicked();
    void on_saveItem_reSet_button_clicked();

signals:
    void continuePaly(int);
    void review(int);
    void deleteMap(int);
    void reSet(int);
private:
    Ui::saveItem *ui;
    int MapID;
};

#endif // SAVEITEM_H
