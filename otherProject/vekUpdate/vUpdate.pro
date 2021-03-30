QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS_RELEASE += -O3
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datacurl.cpp \
    main.cpp \
    vupdate.cpp

HEADERS += \
    datacurl.h \
    vupdate.h

FORMS += \
    vupdate.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  res.qrc

######curl##########
DEFINES += CURL_STATICLIB
LIBS += -L$$PWD/3rdparty/curl/lib/ -lcurl -lssl -lcrypto -lz -ldl
INCLUDEPATH += $$PWD/3rdparty/curl/include
DEPENDPATH += $$PWD/3rdparty/curl/include
LIBS+= $$PWD/3rdparty/curl/lib/libcurl.a
LIBS+= $$PWD/3rdparty/curl/lib/libcrypto.a
LIBS+= $$PWD/3rdparty/curl/lib/libssl.a
LIBS+= $$PWD/3rdparty/curl/lib/libz.a
