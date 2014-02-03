#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);
    int rowCount(const QModelIndex & index);
    int columnCount(const QModelIndex & index);
    QVariant data();
    QVariant headerData();

signals:

public slots:

};

#endif // TABLEMODEL_H
