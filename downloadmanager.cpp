#include "downloadmanager.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

DownloadManager::DownloadManager(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(save(QNetworkReply*)) );

    connect(manager,
            SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
            this,
            SLOT(error(QNetworkAccessManager::NetworkAccessibility )) );
}

void DownloadManager::download(const QString &url )
{
    manager->get( QNetworkRequest(url) );
}

void DownloadManager::save(QNetworkReply* reply)
{
    //qDebug()<<"saving downloadable content:";
    if(reply->error() != 0)
        emit netError("internets not available" );
    else
    {
        if(reply->url().fileName().endsWith(".json"))
        {
            QByteArray data = reply->readAll();
            QJsonObject obj = QJsonDocument::fromJson(data).object();
            emit JsonReady(obj);
        }
        if(reply->url().fileName().endsWith(".png"))
        {
            QByteArray data = reply->readAll();
            QString path = QDir::home().path()+"/.books/"+reply->url().fileName();
            path = QDir::toNativeSeparators(path);
            QFile file( path );
            file.open(QIODevice::ReadWrite);
            file.write(data);
            file.close();
        }
    }
}

void DownloadManager::error(QNetworkAccessManager::NetworkAccessibility status)
{
    if(status == 0)
        emit netError("internets not available" );
}
