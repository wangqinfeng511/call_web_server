#ifndef PHONE_CALL_H
#define PHONE_CALL_H

#include <QObject>
#include "../web_base.h"
class phone_call : public web_base
{
    Q_OBJECT
public:
    explicit phone_call(web_base *parent = nullptr);
    QByteArray get(QString url,QString request_head);
signals:
public slots:
};

#endif // CALL_RECORDS_H
