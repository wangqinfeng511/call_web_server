#ifndef GET_FILE_H
#define GET_FILE_H

#include <QObject>
#include "../web_base.h"
class get_file : public web_base
{
    Q_OBJECT
public:
    explicit get_file(web_base *parent = nullptr);
    QByteArray get(QString url,QString request_head);
signals:

public slots:
};

#endif // CALL_RECORDS_H
