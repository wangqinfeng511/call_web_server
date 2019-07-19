#include "call_records.h"
#include "../web_base.h"
#include<QDebug>
#include<QString>
#include <QJsonObject>
#include <QJsonDocument>
//#include "database.h"
#include "database.h"
call_records::call_records(web_base *parent) : web_base(parent)
{
}
QByteArray call_records::get(QString url,QString request_head){
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
//http://127.0.0.1:1148/call_records?scall=1001&dcall=9002&start_data_time=2019-04-28&end_data_time=2019-04-31"
    QString scall=parent_json.value("scall").toString();
    QString dcall=parent_json.value("dcall").toString();
    QString start_time=parent_json.value("start_time").toString();
    QString end_time=parent_json.value("end_time").toString();
    if (scall==NULL){
        scall="all";}
    else if(dcall==NULL){
        dcall="all";
    };
    database db;
    QJsonArray call_records_list=db.select_call_record(start_time,end_time,scall,dcall);
    QByteArray response_data= QJsonDocument(call_records_list).toJson();
//    qDebug()<<response_data;
    QByteArray head;
    head+="HTTP/1.1 200 OK\r\n";
//    head+="Keep-Alive: timeout=0\r\n";
    head+="connection:close\r\n";
    head+="content-type: application/json; charset=utf-8\r\n";
    head+="status: 200\r\n";

    QString head_length=QString("content-length: %1\r\n\r\n").arg(response_data.size());
   head+=head_length;
   head+=response_data;
   return  head;
}
