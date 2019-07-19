#ifndef CALL_RECORDS_H
#define CALL_RECORDS_H

#include <QObject>
#include "../web_base.h"
class call_records : public web_base
{
    Q_OBJECT
public:
    explicit call_records(web_base *parent = nullptr);
    QByteArray get(QString url,QString request_head);
signals:
public slots:
};

#endif // CALL_RECORDS_H
