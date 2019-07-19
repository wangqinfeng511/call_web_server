#include "user.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "../web_base.h"
#include <QDebug>
#include "../../database.h"
user::user(web_base *parent) : web_base(parent)
{

}
QByteArray user::get(QString url,QString request_head){
    QString request_head_str=request_head.split("\r\n\r\n")[0];
    QStringList request_head_list=request_head_str.split("\r\n");
    QStringList url_parent=request_head_list[0].split(" ")[1].split("?");
    QStringList parent_list;
    QJsonObject parent_json;
    QByteArray data;
    if(url_parent.length()>1){
        parent_list= url_parent[1].split("&");
    }
    for(int i=0;i<parent_list.length();i++){
        parent_json.insert(parent_list[i].split("=")[0],parent_list[i].split("=")[1]);
    }
    QString action=parent_json.value("action").toString();
//    QString user=
    if(action=="select"){
        QString user=parent_json.value("user").toString();
        int user_id=parent_json.value("user_id").toString().toInt();
        if(user=="all" and user.length()){
            database db;
          QJsonArray tmp_data=db.select_users();
          data=QJsonDocument(tmp_data).toJson();
        }else if(user_id>0){
            database db;
           data=QJsonDocument(db.select_user(user_id)).toJson();
         }

    }else if (action=="login") {
        QString user=parent_json.value("user").toString();
        QString passwd=parent_json.value("passwd").toString();
        database db;
        data=QJsonDocument(db.login(user,passwd)).toJson();
    }else if (action=="insert") {
         QString user=parent_json.value("user").toString();
         QString passwd=parent_json.value("passwd").toString();
         database db;
         QJsonObject status=db.add_user(user,passwd);
         data=QJsonDocument(status).toJson();
    }else if (action=="update") {
         int user_id=parent_json.value("user_id").toString().toInt();
         QString passwd=parent_json.value("passwd").toString();
         database db;
         QJsonObject status=db.update_passwd(user_id,passwd);
         data=QJsonDocument(status).toJson();
    }else if (action=="delete") {
        int user_id=parent_json.value("user_id").toString().toInt();
        database db;
        QJsonObject status=db.delete_user(user_id);
        data=QJsonDocument(status).toJson();
    }else if(action=="set_role"){
        int user_id=parent_json.value("user_id").toString().toInt();
        int role_id=parent_json.value("role_id").toString().toInt();
        database db;
        QJsonObject status= db.set_role(user_id,role_id);
        data=QJsonDocument(status).toJson();
    }else if (action=="disable") {

    }
    QByteArray head;
    head+="HTTP/1.1 200 OK\r\n";
//    head+="Keep-Alive: timeout=0\r\n";
    head+="connection:close\r\n";
    head+="content-type: application/json; charset=utf-8\r\n";
    head+="status: 200\r\n";
//    QString data="{'status','OK'}";
    QString head_length=QString("content-length: %1\r\n\r\n").arg(data.size());
   head+=head_length;
   head+=data;
   return  head;
}
