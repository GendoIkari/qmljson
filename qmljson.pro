TEMPLATE = lib
CONFIG += qt plugin c++11
QT += qml

TARGET = qmljsonplugin
DESTDIR = plugins/QmlJson/

MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build

SOURCES += \
    src/qmljsonplugin.cpp \
    src/qmljson.cpp

HEADERS += \
    src/qmljsonplugin.h \
    src/qmljson.h

DISTFILES += \
    src/qmldir \
    README.md \
    LICENSE

pluginfiles.files += \
    src/qmldir

pluginfiles.path += $$DESTDIR

INSTALLS += pluginfiles
