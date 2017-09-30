#pragma once

#include <QNetworkAccessManager>
#include <QObject>
#include <QUrl>
#include <QVariant>

class QmlJson : public QObject {
    Q_OBJECT
    //! Url to get the json.
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    //! The data downloaded from source.
    Q_PROPERTY(QVariant data READ data NOTIFY dataChanged)

public:
    QUrl source();
    void setSource(QUrl source);
    QVariant data();

signals:
    void sourceChanged(QUrl);
    void dataChanged(QVariant);

private:
    QUrl _source;
    QVariant _data;
    QNetworkAccessManager _manager;
};
