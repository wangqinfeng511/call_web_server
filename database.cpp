#include "database.h"
#include <QJsonObject>
#include <QSqlDatabase>
#include "config.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QJsonArray>
database::database(QObject *parent) : QObject(parent)
{

}
QSqlDatabase database::create_db_connect(){
    QSqlDatabase db;
    if (db.contains("connect")){
        db.removeDatabase("connect");
    }
        db=QSqlDatabase::addDatabase("QMYSQL","connect");
        config conf;
        QJsonObject conf_json=conf.read_config();
        db.setHostName(conf_json.value("mysql_ip").toString());
        db.setPort(conf_json.value("mysql_port").toInt());
        db.setDatabaseName(conf_json.value("db_name").toString());
        db.setUserName(conf_json.value("mysql_user").toString());
        db.setPassword(conf_json.value("mysql_password").toString());
//        qDebug()<<conf_json.value("mysql_ip").toString()<<conf_json.value("mysql_port").toInt()<<conf_json.value("db_name").toString()<<conf_json.value("mysql_user").toString()<<conf_json.value("mysql_password").toString();
    return db;
}
QJsonObject database::insert_ccall_record(QJsonObject data){
    QSqlDatabase db=create_db_connect();
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("insert into call_record(scall,dcall,data_time,file) values(:scall,:dcall,STR_TO_DATE(:data_time,'%Y-%m-%d %H:%i:%s'),:file)");
    query.bindValue(":scall",data.value("scall").toString());
    query.bindValue(":dcall",data.value("dcall").toString());
    query.bindValue(":data_time",data.value("data_time").toString());
    query.bindValue(":file",data.value("file").toString());
    query.exec();
    db.close();
    QJsonObject tt;
    return tt;
}
QJsonArray database::select_call_record(QString start_time, QString end_time,QString scall,QString dcall){
    QSqlDatabase db=create_db_connect();
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery query(db);
    QJsonObject tmp_data;
    QJsonArray data_arrry;
    if(scall=="all" and dcall !="all"){
        query.prepare("select id, scall,dcall,data_time,file from  call_record where  dcall=:dcall and data_time between :start_time and :end_time");
        query.bindValue(":dcall",dcall);
        query.bindValue(":start_time",start_time);
        query.bindValue(":end_time",end_time);
    }else if (scall!="all" and dcall=="all") {
        query.prepare("select id, scall,dcall,data_time,file from  call_record where  scall=:scall and data_time between :start_time and :end_time");
        query.bindValue(":scall",scall);
        query.bindValue(":start_time",start_time);
        query.bindValue(":end_time",end_time);
    }else if (scall!="all" and dcall!="all") {
        query.prepare("select id, scall,dcall,data_time,file from  call_record  where  scall=:scall and dcall=:dcall and data_time between :start_time and :end_time");
        query.bindValue(":dcall",dcall);
        query.bindValue(":scall",scall);
        query.bindValue(":start_time",start_time);
        query.bindValue(":end_time",end_time);
    }
    query.exec();
    while (query.next()) {
        tmp_data.insert("scall",query.value("scall").toString());
        tmp_data.insert("dcall",query.value("dcall").toString());
        tmp_data.insert("file",query.value("file").toString());
        tmp_data.insert("id",query.value("id").toInt());
        tmp_data.insert("data_time",query.value("data_time").toString());
        data_arrry.append(tmp_data);
    }
    return  data_arrry;
}
QJsonArray database::select_users(){
    QSqlDatabase db=create_db_connect();
    if(!db.isOpen()){
         db.open();
    }
    QSqlQuery query(db);
    QJsonObject tmp_data;
    QJsonArray data;
    query.prepare("select A.id,A.user,A.passwd from user A");
//    query.prepare("select A.id,A.user,A.passwd, D.name as premission from user A join role B on A.role_id=B.id join role_permission C on B.id=C.role_id join permission D on C.permission_id=D.id");
    query.exec();
    while (query.next()) {
        tmp_data.insert("name",query.value("user").toString());
        tmp_data.insert("id",query.value("id").toInt());
        tmp_data.insert("passwd",query.value("passwd").toString());
        tmp_data.insert("role_id",query.value("role_id").toInt());
        data.append(tmp_data);
    }
    return data;
};
QJsonObject database::select_user(int user_id){
    QSqlDatabase db=create_db_connect();
    QJsonObject data;
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("select A.id,A.user,A.passwd,B.role from user A left join role B on A.role_id=B.id where A.id=:id");
    query.bindValue(":id",user_id);
    query.exec();
    while (query.next()) {
        data.insert( "id", query.value("id").toInt());
        data.insert("user",query.value("user").toString());
        data.insert("passwd",query.value("passwd").toString());
        data.insert("role",query.value("role").toString());
    }
    return data;
}

QJsonObject database::login(QString user,QString passwd){
    QSqlDatabase db=create_db_connect();
    QJsonObject data;
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("select A.id,A.user,A.passwd,D.name as premission from user A join role B on A.role_id=B.id join role_permission C on B.id=C.role_id join permission D on C.permission_id=D.id where A.user=:user and A.passwd=:passwd");
    query.bindValue(":user",user);
    query.bindValue(":passwd",passwd);
    query.exec();
    QString premission;
    int id;
    while (query.next()) {
        if(premission.length()>1){
          premission+=",";
        }
        premission+=query.value("premission").toString();
        id=query.value("id").toInt();
    }
//    premission+="]";
    data.insert("id",id);
    data.insert("user",user);
    data.insert("passwd",passwd);
    data.insert("premission",premission);
    return data;
}
QJsonObject database::add_user(QString user,QString passwd){
    QSqlDatabase db=create_db_connect();
    QJsonObject status;
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("insert user(user,passwd) values(:user,:passwd)");
    query.bindValue(":user",user);
    query.bindValue(":passwd",passwd);
    query.exec();
    status.insert("status","OK");
    return status;
}
QJsonObject database::delete_user(int user_id){
    QJsonObject status;
    if(!user_id>0){
        status.insert("status","id Error");
        return status;
    }else {
        QSqlDatabase db=create_db_connect();
        if(!db.isOpen()){
            db.open();
        }
        QSqlQuery query(db);
        query.prepare("delete from user where id=:user_id");
        query.bindValue(":user_id",user_id);
        query.exec();
        status.insert("status","OK");
    }
    return  status;
}
QJsonObject database::update_passwd(int user_id,QString passwd){
    QJsonObject status;
    QSqlDatabase db =create_db_connect();
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("update  user set passwd=:passwd where id=:user_id");
    query.bindValue(":user_id",user_id);
    query.bindValue(":passwd",passwd);
    query.exec();
    status.insert("status","OK");
    return status;
}
QJsonObject database::set_role(int user_id,int role_id){
    QJsonObject status;
    QSqlDatabase db =create_db_connect();
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("update user set role_id=:role_id where id=:user_id");
    query.bindValue(":role_id",role_id);
    query.bindValue(":user_id",user_id);
    query.exec();
    status.insert("stauts","OK");
    return  status;
}

QJsonArray database::select_role(){
    QSqlDatabase db=create_db_connect();
    if(!db.isOpen()){
        db.open();
    }
    QSqlQuery query(db);
    query.prepare("select id,role from role");
    query.exec();
    QJsonObject tmp_data;
    QJsonArray data;
    while (query.next()) {
        tmp_data.insert("id",query.value("id").toInt());
        tmp_data.insert("name",query.value("role").toString());
        data.append(tmp_data);
    }
    return data;
}
