#pragma once

#include <QByteArray>
#include <QNetworkAccessManager>
#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QVariant>

class QmlJson : public QObject {
    Q_OBJECT
    //! Url to get the json.
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    //! The data downloaded from source.
    Q_PROPERTY(QVariant data READ data NOTIFY dataChanged)
    //! Start and stop polling data from source.
    Q_PROPERTY(bool polling READ polling WRITE setPolling NOTIFY pollingChanged)
    //! This is the polling interval in milliseconds.
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

public:
    QmlJson(QObject* parent = 0);
    QUrl source();
    void setSource(QUrl source);
    QVariant data();
    bool polling();
    void setPolling(bool polling);
    int interval();
    void setInterval(int interval);

signals:
    void sourceChanged(QUrl);
    void dataChanged(QVariant);
    void pollingChanged(bool);
    void intervalChanged(int);

private:
    QUrl _source;
    QVariant _data;
    QTimer _timer;
    QNetworkAccessManager _manager;

private slots:
    void loadData();
    void parseJsonDocument(QByteArray bytes);
};
