QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    demo.cpp \
    main.cpp \

HEADERS += \
    config.h \
    demo.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    login.qrc
include(./ReadyToPlay/ReadyToPlay.pri)
include(./setting/setting.pri)
include(./LoginRegiste/LoginRegiste.pri)
include(./dataHandler/dataHandler.pri)
include(./game/game.pri)
include(./tool/tool.pri)

FORMS += \
    demo.ui

