#ifndef CLASSES_H
#define CLASSES_H

#include <QObject>
#include"student.h"
class classes : public QObject
{
    Q_OBJECT
public:
    explicit classes(QObject *parent = nullptr);
    int class_num;
    QString class_name;
    QString root;
    QString PassWord;

signals:
    void create_class();
};

#endif // CLASSES_H
