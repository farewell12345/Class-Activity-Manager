#ifndef CHANGE_STUDENT_H
#define CHANGE_STUDENT_H

#include <QObject>
#include <QWidget>
#include<QLineEdit>
#include<QString>
#include<QPushButton>
#include<QLabel>
class Change_student : public QWidget
{
    Q_OBJECT
public:
    explicit Change_student(QWidget *parent = nullptr);
    QFont font;
    QLineEdit name,sex,ID;
    QPushButton ok;
    QLabel title[3];
    void init_edit(QLineEdit &);
    void init_title(QLabel &);
signals:

};

#endif // CHANGE_STUDENT_H
