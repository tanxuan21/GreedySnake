#ifndef STARTGAME_H
#define STARTGAME_H


#include <QWidget>
#include "../game/game.h"
#include "../setting/setting.h"
#include "./begin.h"
#include "./picksave.h"
#include "dataHandler/userdata.h"
#include "../game/recordplayer.h"
#include <QScrollArea>
class startGame : public QWidget
{
    Q_OBJECT
public:
    explicit startGame(QWidget *parent = nullptr);
    ~startGame();
    void setUser(userData*);
private:
    Game *game;
    Setting *setting;
    begin *beginwidget;
    QScrollArea *scrollWidget;
    pickSave *pickSaveWidget;
    recordPlayer *player;
    userData *user;
    settingData *setting_data = new settingData();
    Map *map= 0;
    Record *record = 0;

    void createSetting();
    int settingBackmodel=0;

    int CurrentMapID = 0;

signals:
    void backToLogin();
protected:
    void resizeEvent(QResizeEvent *);
};

#endif // STARTGAME_H
