#ifndef PRIMEWIDGET_H
#define PRIMEWIDGET_H

#include <QObject>
#include <QWidget>
#include<QLineEdit>
#include<QLabel>
#include<QListWidget>
#include<QPushButton>
class primeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit primeWidget(QWidget *parent = nullptr);
    QLineEdit get_meet[4];
    QLabel temp[10];
    QListWidget *alredy_Sign,*no_Sign;
    QPushButton creat,ok,closees;
signals:

};

#endif // PRIMEWIDGET_H
