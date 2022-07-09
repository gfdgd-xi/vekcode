QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    objvgit.cpp \
    vgit.cpp

HEADERS += \
    common.h \
    objvgit.h \
    vgit.h

FORMS += \
    vgit.ui

#QMAKE_CXXFLAGS_RELEASE += -O3
#Release:QMAKE_POST_LINK += upx -9 $(DESTDIR_TARGET)
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

##########libgit2#########
LIBS += -L$$PWD/3rdparty/libgit2/lib/ -lgit2 -lpcre -lssl -lcrypto
INCLUDEPATH += $$PWD/3rdparty/libgit2/include
DEPENDPATH += $$PWD/3rdparty/libgit2/include
