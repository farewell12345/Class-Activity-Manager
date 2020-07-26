#include "password_set.h"

#include <QCryptographicHash>
PassWord_set::PassWord_set(QObject *parent) : QObject(parent)
{

}
QString PassWord_set::encrypt(QString password)
{
    QString MD5;
    QByteArray str=QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5);
    MD5.append(str.toHex());
    return MD5;
}
