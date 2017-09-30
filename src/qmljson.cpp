#include "qmljson.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

QUrl QmlJson::source()
{
    return _source;
}

void QmlJson::setSource(QUrl source)
{
    if (source == _source)
        return;

    _source = source;
    emit sourceChanged(source);

    auto reply = _manager.get(QNetworkRequest(source));

    // Update data on success.
    connect(reply, &QNetworkReply::finished, [=]() {
        QJsonDocument payload = QJsonDocument::fromJson(reply->readAll());
        if (payload.isArray())
            _data = payload.array().toVariantList();
        else
            _data = payload.object().toVariantMap();
        emit dataChanged(_data);
    });

    // Network error.
    connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), [=](QNetworkReply::NetworkError error) {
        qWarning() << "QmlJson: network error -" << reply->errorString() << error;
    });
}

QVariant QmlJson::data()
{
    return _data;
}
