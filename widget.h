#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QDialog>
#include<QLineEdit>
#include<QLabel>
#include"create_widget.h"
#include"first_windows.h"
#include"error.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    static QString path;
    QDialog *create_claess_dialog;
    QPushButton sign,SignIn;
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QFont font;
    void create_first_class();
    void try_sign(QString,QString,QString);
    void send();
signals:
    void __send(QString &);
private:
    first_windows *first;
    QString send_name,no_md;
    error er_widget;
    QLabel User,Password_show,classesName;
    double CENTER_x,CENTER_y;
    QDialog Password_wrong;
    QLineEdit class_name;
    QLineEdit root;
    QLineEdit Password;
    void init_text(QLabel &p);
    void init_edit(QLineEdit &p);
    void Init_Sign();
    void Sign();
    void Init_button(QPushButton &p);
    create_Widget sign_widget;
    Ui::Widget *ui;
};

#endif // WIDGET_H
