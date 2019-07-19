#include "ocidatabase.h"
#include <QtSql/QSqlDatabase>
#include "../../config.h"
ocidatabase::ocidatabase(QObject *parent) : QObject(parent)
{

}
QSqlDatabase ocidatabase::create_connect(){
    QSqlDatabase db;
    if (db.contains("connect")){
        db.removeDatabase("connect");
    }
        db=QSqlDatabase::addDatabase("QMYSQL","connect");
        config conf;
        QJsonObject conf_json=conf.read_config();
        db.setHostName(conf_json.value("his_ip").toString());
        db.setPort(conf_json.value("his_port").toInt());
        db.setDatabaseName(conf_json.value("his_database").toString());
        db.setUserName(conf_json.value("his_user").toString());
        db.setPassword(conf_json.value("his_passwd").toString());
//        qDebug()<<conf_json.value("mysql_ip").toString()<<conf_json.value("mysql_port").toInt()<<conf_json.value("db_name").toString()<<conf_json.value("mysql_user").toString()<<conf_json.value("mysql_password").toString();
    return db;
}
