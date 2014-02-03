#ifndef MANAGER_H
#define MANAGER_H

#include "downloadmanager.h"
#include "sqlkepper.h"

#include <QSqlDatabase>
#include <QObject>

class Manager : public QObject
{
    Q_OBJECT

    DownloadManager dm;
    SqlKepper SqKeeper;
    bool errorLock;
public:
    explicit Manager(QObject *parent = 0);
    bool update();
signals:
    void error(const QString& errorMessage);
    void ready();
public slots:
    void readySlot();
    void errorKeeper(const QString message);
};

#endif // MANAGER_H
