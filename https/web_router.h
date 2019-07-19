#ifndef WEB_ROUTER_H
#define WEB_ROUTER_H
#include "web_base.h"
#include <QObject>

class web_router : public QObject
{
    Q_OBJECT
public:
    explicit web_router(QObject *parent = nullptr);
    QByteArray respnse(QString path,QString method,QString request_head);
signals:
    void send_data(QByteArray data);
private:
    QList<web_base*> web_path_list;
public slots:
    void write_data(QByteArray data){
        send_data(data);
    }
};

#endif // WEB_ROUTER_H
