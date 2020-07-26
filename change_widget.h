#ifndef CHANGE_WIDGET_H
#define CHANGE_WIDGET_H

#include <QObject>
#include <QWidget>
#include<QLineEdit>
#include<QString>
class change_widget : public QWidget
{
    Q_OBJECT
public:
    explicit change_widget(QWidget *parent = nullptr);
    QLineEdit name,sex,ID;
    void init_edit(QLineEdit &p);
    QFont font;
signals:

};

#endif // CHANGE_WIDGET_H
