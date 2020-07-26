#ifndef MEETING_H
#define MEETING_H

#include <QObject>
#include <QWidget>
#include<QLabel>
class meeting : public QObject
{
    Q_OBJECT
public:
    explicit meeting(QObject *parent = nullptr);
    QLabel titles[3];
    QString title,number,time,master;
    int no_Sign,already_sign;
signals:

};

#endif // MEETING_H
