QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    banker.cpp \
    box.cpp \
    buildableproperty.cpp \
    charactor.cpp \
    emailGetJailPass.cpp \
    emailGetMoney.cpp \
    emailMove.cpp \
    gameManager.cpp \
    jail.cpp \
    main.cpp \
    mainwindow.cpp \
    mortgagewindow.cpp \
    player.cpp \
    property.cpp \
    restaurant.cpp \
    rolldicewindow.cpp \
    email.cpp \
    emailDeck.cpp \
    tradewindow.cpp

HEADERS += \
    banker.h \
    box.h \
    buildableproperty.h \
    charactor.h \
    emailGetJailPass.h \
    emailGetMoney.h \
    emailMove.h \
    gameManager.h \
    jail.h \
    mainwindow.h \
    mortgagewindow.h \
    player.h \
    property.h \
    restaurant.h \
    rolldicewindow.h \
    email.h \
    emailDeck.h \
    tradewindow.h
    
FORMS += \
    mainwindow.ui \
    mortgagewindow.ui \
    rolldicewindow.ui \
    tradewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
