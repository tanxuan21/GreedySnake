#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class gameInfo;
}

class gameInfo : public QWidget
{
    Q_OBJECT

public:
    explicit gameInfo(QWidget *parent = nullptr);
    ~gameInfo();
    void setText(QString);
protected:
    void paintEvent(QPaintEvent *event);
private slots:

    void on_save_quit_button_clicked();

    void on_continueGame_button_clicked();

    void on_restart_button_clicked();

    void on_exit_button_clicked();

    void on_record_button_clicked();

private:
    Ui::gameInfo *ui;
signals:
    void save_and_quit();
    void continueGame();
    void reStart();
    void exit();
    void recordButton();
};

#endif // GAMEINFO_H
