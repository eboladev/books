#ifndef SQLKEPPER_H
#define SQLKEPPER_H

#include <QObject>
#include <QSqlDatabase>
class SqlKepper : public QObject
{
    Q_OBJECT
    QSqlDatabase db;
    bool error;
public:
    explicit SqlKepper(QObject *parent=0);

signals:
    void dbConnectionError(const QString message);
    void downloadRequest(const QString& url);
    void ready();
public slots:
    void wrapJson(QJsonObject& jsonObj);
};

#endif // SQLKEPPER_H
