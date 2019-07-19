#include "heartbeat.h"
#include<QTimerEvent>
#include<QDebug>
#include "config.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>
#include <QJsonObject>
heartbeat::heartbeat(QObject *parent) : QObject(parent)
{
startTimer(1000*5);
}
void heartbeat::timerEvent(QTimerEvent *event){
//    qDebug()<<"sadfasdf";
//    startTimer(1000*5);
    QNetworkAccessManager marger;
    QNetworkRequest request;
//    /api/v1.1.0/heartbeat?token={token}
    QSslConfiguration ca;
    ca.setPeerVerifyMode(QSslSocket::VerifyNone);
    ca.setProtocol(QSsl::TlsV1_0);
    //url
    config conf;
    QJsonObject conf_json=conf.read_config();
    request.setSslConfiguration(ca);
    QString ip=conf_json.value("IP").toString();
    int port=conf_json.value("Port").toInt();
    QString port_str=QString("%1").arg(port);
    QString url=QString("https://%1:%2/api/v1.1.0/heartbeat?token=%3").arg(ip,port_str,token);
    request.setUrl(url);
    QNetworkReply *rsp= marger.get(request);
    rsponse=rsp;
    connect(&marger,SIGNAL(finished(QNetworkReply *)),this,SLOT(responsp_data(QNetworkReply *)));
    connect(rsp,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(write_log(QNetworkReply::NetworkError)));
}
