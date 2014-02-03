#include "JsonGetter.h"

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>


JsonGetter::JsonGetter(QObject* object):
    QObject(object)
{

}

JsonGetter::JsonGetter(QString url)
{
    manager = new QNetworkAccessManager(this);
    connect(manager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(saveReply(QNetworkReply*)) );
    connect(manager,
            SIGNAL(QNetworkReply::NetworkError),
            this,
            SLOT(error(QNetworkReply::NetworkError )) );

    //downloadJson(url);
    manager->get( QNetworkRequest(url) );
}

void JsonGetter::downloadJson(QString url)
{
    manager->get( QNetworkRequest(url) );
}

void JsonGetter::saveReply(QNetworkReply* reply)
{
    downDoc = QJsonDocument::fromBinaryData(reply->readAll());
    emit success();
}

QString JsonGetter::error(QNetworkReply::NetworkError error)
{
    emit netError();
    return "error happens"+QString(error);
}
