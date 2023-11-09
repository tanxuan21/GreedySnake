#ifndef PICKSAVE_H
#define PICKSAVE_H

#include <QWidget>

namespace Ui {
class pickSave;
}

class pickSave : public QWidget
{
    Q_OBJECT

public:
    explicit pickSave(QWidget *parent = nullptr);
    ~pickSave();

private slots:
    void on_pickSave_back_button_clicked();

private:
    Ui::pickSave *ui;
signals:
    void backToBegin();
};

#endif // PICKSAVE_H
