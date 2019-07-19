#include "socket_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QDir>
#include "config.h"
#include "database.h"
socket_server::socket_server()
{
    config conf;
    conf_json= conf.read_config();
    get_token();
    connect(this,SIGNAL(start_down_muse()),this,SLOT(down_muse_file()));
    connect(rsp,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(requst_error(QNetworkReply::NetworkError)));
}
void socket_server::incomingConnection(qintptr soketDescriptor){
    tcp_socket *socket=new tcp_socket(soketDescriptor);
    connect(socket,SIGNAL(readyRead()),socket,SLOT(Read_data()));
    QThread *socket_task=new QThread();
    connect(this,SIGNAL(send_token(QString)),socket,SLOT(set_token(QString)));
    connect(socket,SIGNAL(return_file_name(QString)),this,SLOT(get_random(QString)));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),socket,SLOT(tcp_socket_error(QAbstractSocket::SocketError)));
    socket->moveToThread(socket_task);
    send_token(token);
    socket_task->start();
}
void socket_server::get_token(){
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest req;
    req.setSslConfiguration(config);
    QString IP=conf_json.value("IP").toString();
    int Port=conf_json.value("Port").toInt();
    QString port_str=QString("%1").arg(Port);
    QString list_ip=conf_json.value("list_ip").toString();
    int list_port=conf_json.value("list_port").toInt();
    QString url=QString("https://%1:%2/api/v1.10/login").arg(IP,port_str);
    req.setUrl(QUrl(url));
    QJsonObject data;
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QCryptographicHash t(QCryptographicHash::Md5);
    t.addData("Wangqinfeng511");
    data.insert("username","api");
    QString ps=t.result().toHex();
    data.insert("password",ps);
    data.insert("url",list_ip);
    data.insert("port",list_port);
    rsp= manager->post(req,QJsonDocument(data).toJson());
    connect(manager,SIGNAL(finished(QNetworkReply *)),this,SLOT(set_token(QNetworkReply *)));
}

void socket_server::down_muse_file(){
    QString IP=conf_json.value("IP").toString();
    int Port=conf_json.value("Port").toInt();
    QString port_str=QString("%1").arg(Port);
//    down_file_name="20190426155521-1556265319.2739-9001-9002-Internal.wav";
    QString url=QString("https://%4:%5/api/v1.1.0/recording/download?recording=%1&random=%2&token=%3").arg(down_file_name,random_str,token,IP,port_str);
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest req;
    req.setSslConfiguration(config);
    req.setUrl(QUrl(url));
    QNetworkReply *response= manager->get(req);
    rsp=response;
    connect(response,SIGNAL(readyRead()),this,SLOT(write_muse_file()));

}



void socket_server::set_token(QNetworkReply *rsp){
    QByteArray buf = rsp->readAll();
    QJsonObject data= QJsonDocument::fromJson(buf).object();
    token=data.value("token").toString();
    send_token(token);
}

void socket_server::get_random(QString file_name){
    QString IP=conf_json.value("IP").toString();
    int Port=conf_json.value("Port").toInt();
    QString port_str=QString("%1").arg(Port);
    QString url=QString("https://%2:%3/api/v1.1.0/recording/get_random?token=%1").arg(token,IP,port_str);
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest req;
    req.setSslConfiguration(config);
    req.setUrl(QUrl(url));
    QJsonObject data;
    data.insert("recording",file_name);
    rsp=manager->post(req,QJsonDocument(data).toJson());
    connect(manager,SIGNAL(finished(QNetworkReply *)),this,SLOT(set_random_str(QNetworkReply *)));

    //
}

void socket_server::write_muse_file(){
   QString path_str=conf_json.value("Muse_path").toString();
   QDir muse_path(path_str);
   if(!muse_path.exists()){
       muse_path.mkpath("./");
   }
//   qDebug()<<down_file_name;
   QString file_path=QString("%1/%2").arg(muse_path.absolutePath(),down_file_name);
   if(down_file_name.length()>1){
       QFile file(file_path);
          file.open(QIODevice::ReadWrite);
          file.seek(file.size());
          file.write(rsp->readAll());
          file.close();
   }

}








//socket _file

tcp_socket::tcp_socket(int soketdesc,QTcpSocket *parent):QTcpSocket(parent)
{
    this->setSocketDescriptor(soketdesc);
    config conf;
    conf_json= conf.read_config();
}
void tcp_socket::Read_data(){
    QString data=this->readAll();
    QString str_json=data.split("\r\n\r\n")[1];
    QByteArray byte_json= str_json.toLocal8Bit();
    QJsonObject rsp=QJsonDocument::fromJson(byte_json).object();
    QString active=rsp.value("action").toString();
    if(active=="NewCdr"){
        QString muse_name=rsp.value("recording").toString();
        database db;
        QJsonObject tmp_data;
//        scall,dcall,data_time,file
        tmp_data.insert("dcall",rsp.value("callto").toString());
        tmp_data.insert("scall",rsp.value("callfrom").toString());
        tmp_data.insert("data_time",rsp.value("timestart").toString());
        tmp_data.insert("file",rsp.value("recording").toString());
        db.insert_ccall_record(tmp_data);
/*        {"action":"NewCdr",
 * "callduraction":"4",
 * "callfrom":"9002",
 * "callid":"1556268469.2846",
 * "callto":"9001",
 * "recording":"20190426164750-1556268469.2846-9002-9001-Internal.wav",
 * "sn":"369464294833",
 * "status":"ANSWERED",
 * "talkduraction":"2",
 * "timestart":"2019-04-26 16:47:49",
 * "type":"Internal"}*/
        return_file_name(muse_name);
    }
    this->write("HTTP/1.1 200 OK\r\n");

}


