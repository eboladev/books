#include "detailedinfowindow.h"
#include "ui_detailedinfowindow.h"

#include <QImage>
#include <QPixmap>
#include <QPalette>

detailedInfoWindow::detailedInfoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detailedInfoWindow)
{
    ui->setupUi(this);

    author_name = ui->author;
    title = ui->title;
    _pay_way = ui->PayWay;
    picture = ui->picture;

    picture->setBackgroundRole(QPalette::Base);
}

detailedInfoWindow::~detailedInfoWindow()
{
    delete ui;
}
/* /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// */
void detailedInfoWindow::setPicture(const QString& path)
{
    QImage image(path);
    picture->setPixmap(QPixmap::fromImage(image));
}

void detailedInfoWindow::setAuthorName(const QString &_name)
{

}

void detailedInfoWindow::setTitle(const QString &_title)
{

}

void detailedInfoWindow::setPayWay(const QString &_pay_way)
{

}
