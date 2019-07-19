#include "phone_call.h"
#include "../web_base.h"
#include<QDebug>
#include<QString>
#include <QJsonObject>
phone_call::phone_call(web_base *parent) : web_base(parent)
{
}
QByteArray phone_call::get(QString url,QString request_head){
    QString request_head_str=request_head.split("\r\n\r\n")[0];
    QStringList request_head_list=request_head_str.split("\r\n");
    QStringList url_parent=request_head_list[0].split(" ")[1].split("?");
    QStringList parent_list;
    QJsonObject parent_json;
    if(url_parent.length()>1){
        parent_list= url_parent[1].split("&");
    }
    for(int i=0;i<parent_list.length();i++){
        parent_json.insert(parent_list[i].split("=")[0],parent_list[i].split("=")[1]);
    }
    //    qDebug()<<parent_json;

    QByteArray head;
    head+="HTTP/1.1 200 OK\r\n";
//    head+="Keep-Alive: timeout=0\r\n";
    head+="connection:close\r\n";
    head+="content-type: application/json; charset=utf-8\r\n";
    head+="status: 200\r\n";
    QString data="{'status','OK'}";
    QString head_length=QString("content-length: %1\r\n\r\n").arg(data.size());
   head+=head_length;
   head+=data;
   return  head;
}
