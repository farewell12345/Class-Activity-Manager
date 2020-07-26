#ifndef ERROR_H
#define ERROR_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
class error:public QWidget
{
    Q_OBJECT
public:
    QLabel error_text,class_name,class_num,class_user;
    error();
};

#endif // ERROR_H
