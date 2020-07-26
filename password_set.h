#ifndef PASSWORD_SET_H
#define PASSWORD_SET_H

#include <QObject>

class PassWord_set : public QObject
{
    Q_OBJECT
public:
    explicit PassWord_set(QObject *parent = nullptr);
    static QString encrypt(QString password);
signals:

};

#endif // PASSWORD_SET_H
