#-------------------------------------------------
# 天气预报
#-------------------------------------------------

INCLUDEPATH         += $$PWD/include

HEADERS += \
    $$PWD/include/json.h \
    $$PWD/include/citybook.h \
    $$PWD/include/weatherwidget.h \
    $$PWD/include/weatherapi.h \
    $$PWD/include/citymanagerwidget.h \
    $$PWD/include/qtwaitwidget.h

SOURCES += \
    $$PWD/src/json.cpp \
    $$PWD/src/citybook.cpp \
    $$PWD/src/weatherwidget.cpp \
    $$PWD/src/weatherapi.cpp \
    $$PWD/src/citymanagerwidget.cpp \
    $$PWD/src/qtwaitwidget.cpp
