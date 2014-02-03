#ifndef DETAILEDINFOWINDOW_H
#define DETAILEDINFOWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QString>

namespace Ui {
class detailedInfoWindow;
}

class detailedInfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit detailedInfoWindow(QWidget *parent = 0);
    ~detailedInfoWindow();
    void setAuthorName(const QString& _name);
    void setTitle(const QString& _title);
    void setPayWay(const QString& _pay_way);
    void setPicture(const QString& path);
private:
    Ui::detailedInfoWindow *ui;

    QLabel* author_name;
    QLabel* title;
    QLabel* _pay_way;
    QLabel* picture;

};

#endif // DETAILEDINFOWINDOW_H
