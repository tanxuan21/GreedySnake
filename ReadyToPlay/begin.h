#ifndef BEGIN_H
#define BEGIN_H

#include <QWidget>

namespace Ui {
class begin;
}

class begin : public QWidget
{
    Q_OBJECT

public:
    explicit begin(QWidget *parent = nullptr);
    ~begin();

private slots:
    void on_begin_setting_button_clicked();

    void on_begin_loginOut_button_clicked();

    void on_begin_startNewGame_Button_clicked();

private:
    Ui::begin *ui;
signals:
    void toSetting();
    void backToLogin();
    void newGame();
};

#endif // BEGIN_H
