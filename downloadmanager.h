#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QNetworkReply>

class DownloadManager : public QObject
{
    Q_OBJECT

    QNetworkAccessManager* manager;
public:
    explicit DownloadManager(QObject *parent = 0);
    QString error(QNetworkReply::NetworkError error);

signals:
    void netError(const QString message);
    void JsonReady(QJsonObject& docObj);
public slots:
    void download(const QString &url);
    void save(QNetworkReply* reply);
    void error(QNetworkAccessManager::NetworkAccessibility status);
};

#endif // DOWNLOADMANAGER_H
