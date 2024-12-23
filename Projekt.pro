QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dane/assortment.cpp \
    Dane/ingredient.cpp \
    Dane/order.cpp \
    Dane/ordermanager.cpp \
    addnewassortment.cpp \
    addnewingredient.cpp \
    addneworder.cpp \
    assortmentmanager.cpp \
    ingredientmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    orderprinter.cpp

HEADERS += \
    Dane/assortment.hpp \
    Dane/ingredient.hpp \
    Dane/order.hpp \
    Dane/ordermanager.hpp \
    addnewassortment.hpp \
    addnewingredient.hpp \
    addneworder.hpp \
    assortmentmanager.hpp \
    ingredientmanager.hpp \
    mainwindow.hpp \
    orderprinter.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
