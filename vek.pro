QT = widgets
QT += concurrent
CONFIG += c++17
CONFIG += static
CONFIG += staticlib
CONFIG += release
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
QMAKE_CXXFLAGS += -Wno-unused-value
QMAKE_CXXFLAGS += -Wmissing-field-initializers
QMAKE_CXXFLAGS += -Wreturn-type
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS_RELEASE += -O3       # Release -O3
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS += vek_zh_CN.ts\
                vek_us_EN.ts
SOURCES += \
    main.cpp \
  src/objectAddGameAT.cpp \
  src/objectAddGameMT.cpp \
    src/objectExtend.cpp \
    src/objectJson.cpp \
  src/objectProcManage.cpp \
    src/objectSource.cpp \
    src/vek.cpp \
    src/vekAbout.cpp \
  src/vekExportJson.cpp \
  src/vekGameAddAT.cpp \
  src/vekGameAddMT.cpp \
  src/vekGameAddMulti.cpp \
    src/vekGameData.cpp \
    src/vekGameListView.cpp \
    src/vekGamePanel.cpp \
    src/vekGetCurl.cpp \
    src/vekGitWine.cpp \
  src/vekInitObject.cpp \
    src/vekSourceEdit.cpp \
    src/vekExtendDebug.cpp \
    src/vekWineOption.cpp \

HEADERS += \
    src/baseData.h \
    src/baseRes.h \
    src/common.h \
    src/objectAddGameAT.h \
    src/objectAddGameMT.h \
    src/objectExtend.h \
    src/objectJson.h \
    src/objectProcManage.h \
    src/objectSource.h \
    src/ui_common.h \
    src/vek.h \
    src/vekAbout.h \
    src/vekExportJson.h \
    src/vekExtendDebug.h \
    src/vekGameAddAT.h \
    src/vekGameAddMT.h \
    src/vekGameAddMulti.h \
    src/vekGameData.h \
    src/vekGameListView.h \
    src/vekGamePanel.h \
    src/vekGetCurl.h \
    src/vekGitWine.h \
    src/vekInitObject.h \
    src/vekSourceEdit.h \
    src/vekWineOption.h

FORMS += \
    ui/vekExportJson.ui \
    ui/vekGameAddAT.ui \
    ui/vekGameAddMT.ui \
    ui/vekGameAddMulti.ui \
    ui/vekSourceEdit.ui \
    ui/vek.ui \
    ui/vekAbout.ui \
    ui/vekExtendDebug.ui \
    ui/vekWineOption.ui

#DEBUG
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

#UPX
#Release:QMAKE_POST_LINK += ./upx -9 $(DESTDIR_TARGET)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    vek_res.qrc

RC_ICONS = res\img\vek.ico
VERSION = 1.0.0.0

DISTFILES += \
    vek_us_EN.ts \
    vek_zh_CN.ts

######curl##########
DEFINES += CURL_STATICLIB
LIBS += -L$$PWD/3rdparty/curl/lib/ -lcurl -lssl -lcrypto -lz -ldl

INCLUDEPATH += $$PWD/3rdparty/curl/include
DEPENDPATH += $$PWD/3rdparty/curl/include

LIBS+= $$PWD/3rdparty/curl/lib/libcurl.a
LIBS+= $$PWD/3rdparty/curl/lib/libcrypto.a
LIBS+= $$PWD/3rdparty/curl/lib/libssl.a
LIBS+= $$PWD/3rdparty/curl/lib/libz.a
#########rapidjson########
INCLUDEPATH += $$PWD/3rdparty/json
DEPENDPATH += $$PWD/3rdparty/json
##########libgit2#########
unix:!macx: LIBS += -L$$PWD/3rdparty/libgit2/lib/ -lgit2 -lpcre -lssl -lcrypto
INCLUDEPATH += $$PWD/3rdparty/libgit2/include
DEPENDPATH += $$PWD/3rdparty/libgit2/include
unix:!macx: PRE_TARGETDEPS += $$PWD/3rdparty/libgit2/lib/libgit2.a
unix:!macx: PRE_TARGETDEPS += $$PWD/3rdparty/libgit2/lib/libcrypto.a
unix:!macx: PRE_TARGETDEPS += $$PWD/3rdparty/libgit2/lib/libssl.a
