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

private:
    Ui::saveItem *ui;
};

#endif // SAVEITEM_H
