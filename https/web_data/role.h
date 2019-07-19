#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include "../web_base.h"
class role : public web_base
{
    Q_OBJECT
public:
    explicit role(web_base *parent = nullptr);
    QByteArray get(QString url,QString request_head);
signals:

public slots:
};

#endif // ROLE_H
