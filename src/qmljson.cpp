#include "qmljson.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

QmlJson::QmlJson(QObject* parent)
    : QObject(parent)
{
    connect(&_timer, &QTimer::timeout, this, &QmlJson::loadData);
}

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

    loadData();
}

QVariant QmlJson::data()
{
    return _data;
}

bool QmlJson::polling()
{
    return _timer.isActive();
}

void QmlJson::setPolling(bool polling)
{
    if (_timer.isActive() == polling)
        return;

    if (polling)
        _timer.start();
    else
        _timer.stop();

    emit pollingChanged(polling);
}

int QmlJson::interval()
{
    return _timer.interval();
}

void QmlJson::setInterval(int interval)
{
    if (_timer.interval() == interval)
        return;
    _timer.setInterval(interval);
    emit intervalChanged(interval);
}

void QmlJson::loadData()
{
    auto reply = _manager.get(QNetworkRequest(_source));

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
