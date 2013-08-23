QT       += core gui
QT       += opengl

TARGET = LetsTank
TEMPLATE = app

SOURCES += main.cpp \
    tank.cpp \
    model.cpp \
    human_tank.cpp \
    helpfun.cpp \
    gun.cpp \
    glwidget.cpp \
    errorlog.cpp \
    engine.cpp \
    computer_tank.cpp \
    collisionengine.cpp \
    camera.cpp \
    bullets.cpp \
    barrel.cpp \
    anti_tank_gun.cpp \
    anti_human_gun.cpp

OTHER_FILES += \
    LetsTank2.pro.user \
    LetsTank.pro.user

HEADERS += \
    tank.h \
    model.h \
    human_tank.h \
    helpfun.h \
    gun.h \
    glwidget.h \
    errorlog.h \
    engine.h \
    computer_tank.h \
    collisionengine.h \
    camera.h \
    bullets.h \
    barrel.h \
    anti_tank_gun.h \
    anti_human_gun.h

