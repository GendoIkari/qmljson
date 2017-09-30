#include "qmljsonplugin.h"
#include "qmljson.h"
#include <QQmlEngine>

void QmlJsonPlugin::registerTypes(const char* uri)
{
    qmlRegisterType<QmlJson>(uri, 1, 0, "QmlJson");
}
