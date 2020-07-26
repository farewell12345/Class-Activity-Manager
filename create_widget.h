#ifndef CREATE_WIDGET_H
#define CREATE_WIDGET_H

#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include"classes.h"
#include<QDialog>
class create_Widget:public QWidget
{
    Q_OBJECT
public:
    QString path;
    create_Widget();
    QFont font;
signals:
public slots:
private:
    classes *this_class;
    QLabel class_name,root_name,Password_name,confirm,student_num,wrong;
    QLineEdit get_class_name,root,Password,confirm_Password,get_class_num;
    QPushButton Sign_OK;
    void init_pushButton(QPushButton &p);
    void init_edit(QLineEdit &p);
    void init_lable(QLabel &p);
    void sign_Ok_onclicked();
};

#endif // CREATE_WIDGET_H
