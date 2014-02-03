#include "manager.h"

#include <QJsonObject>
#include <QString>
#include <QDir>

Manager::Manager(QObject *parent) :
    QObject(parent),
    errorLock(false)
{
    QDir dirMan;
    //SqKeeper = new SqlKepper(this, db);
    connect(&dm,
            SIGNAL(JsonReady(QJsonObject&)),
            &SqKeeper,
            SLOT(wrapJson(QJsonObject&)));

    connect(&SqKeeper,
            SIGNAL(downloadRequest(const QString&)),
            &dm,
            SLOT(download(const QString&)));

    connect(&SqKeeper,
            SIGNAL(ready()),
            this,
            SLOT(readySlot()) );

    connect(&dm,
            SIGNAL(netError(const QString)),
            this,
            SLOT(errorKeeper(const QString)) );

    connect(&SqKeeper,
            SIGNAL(dbConnectionError(const QString)),
            this,
            SLOT(errorKeeper(const QString)) );

    QString path = QDir::homePath()+"/.books";
    path = QDir::toNativeSeparators(path);
    dirMan.mkdir(path);
    dirMan.setPath(path);
}

bool Manager::update()
{
    if(!errorLock)
        dm.download(QString("http://test.tochkak.ru/list.json"));
    else
    {
        emit ready();
        emit error("network not available, database not update");
    }
}


void Manager::readySlot()
{
    emit ready();
}

void Manager::errorKeeper(const QString message)
{
    errorLock = true;
    emit error(message);
    emit ready();
}
