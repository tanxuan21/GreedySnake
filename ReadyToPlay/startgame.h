#ifndef STARTGAME_H
#define STARTGAME_H


#include <QWidget>
#include "../game/game.h"
#include "../setting/setting.h"
#include "./begin.h"
#include "./picksave.h"
#include <QScrollArea>
class startGame : public QWidget
{
    Q_OBJECT
public:
    explicit startGame(QWidget *parent = nullptr);
    ~startGame();
private:
    Game *game;
    Setting *setting;
    begin *beginwidget;
    QScrollArea *scrollWidget;
    pickSave *pickSaveWidget;
    void createSetting();
    int settingBackmodel=0;
signals:
    void backToLogin();
protected:
    void resizeEvent(QResizeEvent *);
private slots:
    void on_begin_loginOut_button_clicked();
    void on_begin_startNewGame_Button_clicked();

};

#endif // STARTGAME_H
