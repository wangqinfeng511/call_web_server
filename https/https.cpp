#include "https.h"
#include <QTcpSocket>
#include <QThread>
#include <QtDebug>
#include <QJsonObject>
#include <QtNetwork/QNetworkRequest>
#include "web_router.h"
//https::https(QObject *parent) : QObject(parent)
//{

//}
https::https(){

}
void https::incomingConnection(qintptr socketDescriptor){
    request_connect *http_socket=new request_connect(socketDescriptor);
    QThread *request_task=new QThread();
    http_socket->moveToThread(request_task);
    connect(http_socket,SIGNAL(readyRead()),http_socket,SLOT(Read_data()));
    connect(http_socket,SIGNAL(disconnected()),request_task,SLOT(quit()));
    request_task->start();
}


request_connect::request_connect(int socketDesc,QTcpSocket *parent):QTcpSocket(parent)
{
    this->setSocketDescriptor(socketDesc);
}
void request_connect::Read_data(){
    QString response_head= this->readAll();
    QString head=response_head.split("\r\n\r\n")[0];
    QStringList head_list=head.split("\r\n");
    QStringList path_and_method=head_list[0].split(" ");
    QString method=path_and_method[0];
    QString path=path_and_method[1];
    web_router router;
    QByteArray response_byte;
    response_byte= router.respnse(path.split("?")[0],method,response_head);
    if(this->isValid()){
           this->write(response_byte);
    }
}

