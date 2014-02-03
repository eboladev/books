#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "manager.h"
#include "detailedinfowindow.h"

#include <QMainWindow>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QWidget>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Update_clicked();
    void onTableElementClicked ( const QModelIndex&  index );
    void updateView();
    void showError(const QString errorMessage);
private:
    Ui::MainWindow *ui;
    QTableView* table;
    QSqlRelationalTableModel* sqlModel;
    QSqlDatabase db;
    Manager *manager;
    detailedInfoWindow *infoWindow;
    QLabel *picture;
};

#endif // MAINWINDOW_H
