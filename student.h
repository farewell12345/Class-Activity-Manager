#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    Student(QObject *parent=nullptr);
    QString name;
    QString sex;
    QString ID;
private:

signals:

};

#endif // STUDENT_H
