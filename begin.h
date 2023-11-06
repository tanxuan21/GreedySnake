#ifndef BEGIN_H
#define BEGIN_H

#include <QWidget>
#include "./game.h"
namespace Ui {
class begin;
}

class begin : public QWidget
{
    Q_OBJECT

public:
    explicit begin(QWidget *parent = nullptr);
    ~begin();

private:
    Ui::begin *ui;
    Game *game;
signals:
    void backToLogin();
private slots:
    void on_begin_loginOut_button_clicked();
    void on_begin_startNewGame_Button_clicked();
};

#endif // BEGIN_H
