#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "log.h"
class socket_server : public QTcpServer
{
    Q_OBJECT
public:
    socket_server();
protected:
    void incomingConnection(qintptr soketDescriptor);
    void get_token();
signals:
    void send_token(QString token);
    void start_down_muse();
public slots:
    void set_token(QNetworkReply *rsp);
    void get_random(QString file_name);
    void set_random_str(QNetworkReply *dom){
       QByteArray rspose_json=dom->readAll();
        QJsonObject data=QJsonDocument::fromJson(rspose_json).object();
        random_str=data.value("random").toString();
        down_file_name=data.value("recording").toString();
        start_down_muse();
    }
    void down_muse_file();
    void write_muse_file();
    void requst_error(QNetworkReply::NetworkError error){
        log write_log;
        QNetworkRequest t= rsp->request();
        QString url=t.url().toString();
        QString error_str=rsp->errorString();
        QString url_error=QString("%1  %2").arg(url,error_str);
        write_log.append_log(url_error);
    }
private:
    QString token;
    QString down_file_name;
    QString random_str;
    QNetworkReply *rsp;
    QJsonObject conf_json;
};


class tcp_socket:public QTcpSocket{
    Q_OBJECT
public:
    tcp_socket(int soketdesc,QTcpSocket *parent=NULL);
private:
    QString token;
     QJsonObject conf_json;
private slots:
    void Read_data();
    void set_token(QString tokens){
        token=tokens;
    }
    void tcp_socket_error(QAbstractSocket::SocketError error){
        QString error_str=this->errorString();
//        log write_log;
//        write_log.append_log(error_str);
    }
signals:
        void return_file_name(QString f_n);
};

#endif // SOCKET_SERVER_H

