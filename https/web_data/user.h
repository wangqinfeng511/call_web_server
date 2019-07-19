#ifndef USER_H
#define USER_H

#include <QObject>
#include "../web_base.h"
class user : public web_base
{
    Q_OBJECT
public:
    explicit user(web_base *parent = nullptr);
    QByteArray get(QString url,QString request_head);
signals:

public slots:
};

#endif // USER_H
