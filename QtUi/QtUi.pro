TEMPLATE = lib
TARGET = QtUi
QT += widgets
CONFIG += c++11

DESTDIR         = $$PWD/../thirdpart/libqui/lib
MOC_DIR         = $$PWD/../build/qui
OBJECTS_DIR     = $$PWD/../build/qui

# Input
SOURCES += \
        $$PWD/src/launcherwidget.cpp \
        $$PWD/src/qtwidgetbase.cpp \
        $$PWD/src/qtpixmapbutton.cpp

HEADERS += \
        $$PWD/include/launcherwidget.h \
        $$PWD/include/qtwidgetbase.h \
        $$PWD/include/qtpixmapbutton.h

INCLUDEPATH     += $$PWD/include

unix {
    src_dir = $$PWD/include/*.h
    QtUi = $$PWD/include/QtUi
    dst_dir = $$PWD/../thirdpart/libqui/include/

    !exists($$dst_dir): system(mkdir -p $$dst_dir)

    system(cp $$src_dir $$dst_dir -arf)
    system(cp $$QtUi $$dst_dir -arf)
}


RESOURCES += \
    ../Skin/Resource.qrc
