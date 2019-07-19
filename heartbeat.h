#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <QObject>
#include<QDebug>
#include <QNetworkReply>
#include "log.h"
class heartbeat : public QObject
{
    Q_OBJECT
public:
    explicit heartbeat(QObject *parent = nullptr);

signals:
protected:
    void timerEvent(QTimerEvent *event);
private:
    QString token;
    QNetworkReply *rsponse;
public slots:
    void set_token(QString token_str){
        if(token_str.length()>1){
            token=token_str;
        }
    }
    void write_log(QNetworkReply::NetworkError error){
        log write_log;
        write_log.append_log(rsponse->errorString());
    }
    void responsp_data(QNetworkReply *dom){
        qDebug()<<dom->readAll();
    }
};

#endif // HEARTBEAT_H
