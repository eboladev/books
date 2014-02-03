#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlRelationalTableModel>
#include <QSqlDatabase>
#include <QtSql>
#include <QModelIndex>
#include <QMap>
#include <QItemSelectionModel>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table = ui->tableView;
    picture = ui->picture;

    /* ***************************** */
    manager = new Manager(this);

    db =  QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dbname.sqlite");
    db.open();

    sqlModel = new QSqlRelationalTableModel(this, db);
    sqlModel->setTable("books");

    table->setModel(sqlModel);

    picture->setBackgroundRole(QPalette::Base);
    /* ********************************************** */

    connect(table,
            SIGNAL(pressed(QModelIndex)),
            this,
            SLOT(onTableElementClicked(const QModelIndex&))
                );
    connect(manager,
            SIGNAL(ready()),
            this,
            SLOT(updateView()));

    connect(manager,
            SIGNAL(error(const QString)),
            this,
            SLOT(showError(const QString)) );

    /* ********************************************** */
    //ui->statusBar->showMessage(tr("please wait..."));
    //ui->centralWidget->setDisabled(true);
    //manager->update();
    on_Update_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
    delete sqlModel;
}

void MainWindow::on_Update_clicked()
{

    ui->statusBar->showMessage(tr("updated..."));
    ui->centralWidget->setDisabled(true);
    manager->update();
}

void MainWindow::onTableElementClicked (const QModelIndex &index )
{
    QModelIndexList row = table->selectionModel()->selectedIndexes();

    QImage image(QDir::home().path()+"/.books/"+row[4].data().toString());
    picture->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::updateView()
{
    sqlModel->setTable("books");

    table->verticalHeader()->hide();
    table->setSortingEnabled(true);
    table->setShowGrid(0);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnHidden(0, true);
    table->setColumnHidden(4, true);

    ui->statusBar->showMessage(tr("ready"));

    ui->centralWidget->setEnabled(true);
    sqlModel->select();
}

void MainWindow::showError(const QString errorMessage)
{
    ui->statusBar->showMessage(errorMessage);
}
