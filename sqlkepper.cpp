#include "sqlkepper.h"

#include <QDir>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlError>
#include <QDebug>
#include <QtSql>

SqlKepper::SqlKepper(QObject *parent) :
    QObject(parent)
{
    //db = QSqlDatabase::database("qSQLITE3connection");
    //qDebug()<<"SqlKepper instance state: "<<db.isOpen();
    /*
    if(!(db.open() ))
    {
        error=true;
        qDebug()<<"db opening error: "<<db.lastError();
    }
    */
}

void SqlKepper::wrapJson(QJsonObject& jsonObj)
{
    db = QSqlDatabase::database("qSQLITE3connection");
    if(!db.isOpen())
    {
        emit dbConnectionError("db not available");
    }
    QSqlQuery query(db);
    qDebug()<<"query state: "<<query.exec("DROP TABLE IF EXISTS BOOKS ;");
    qDebug()<<"query state: "<<query.exec("CREATE TABLE BOOKS(id INTEGER , title VARCHAR(255), author_title VARCHAR(255), free VARCHAR(24), img VARCHAR(255) );");

    QJsonArray arr = jsonObj.value("books").toArray();


    foreach (QJsonValue cortaige, arr)
    {
        QJsonObject node = cortaige.toObject();

        QString image = node.value("img").toString();
        emit downloadRequest(image);
        int start =  image.lastIndexOf("/")+1;
        int end =  image.lastIndexOf("?");
        image.resize(end);
        image = image.right(image.length() - start);

        QString paid;
        if(node.value("free").toString().toInt () == 0)
            paid="non-free";
        if(node.value("free").toString().toInt () == 1)
            paid="free";

        qDebug()<<"query state: "<<query.exec(QString(" INSERT INTO BOOKS VALUES(%1, '%2', '%3', '%4', '%5');")
                  .arg( node.value("id").toString().toInt()   )
                  .arg( node.value("title").toString() )
                  .arg( node.value("author_title").toString() )
                  .arg(  paid  )
                  .arg( image ) );
        qDebug()<<query.lastError();

    }
    emit ready();
}

