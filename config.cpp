#include "config.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QDebug>
config::config(QObject *parent) : QObject(parent)
{

}
QJsonObject config::read_config(){
    QDir config_dir("./");
    QString file_path=QString("%1/%2").arg(config_dir.absolutePath(),"config.conf");
    QFile conf(file_path);
    QJsonObject conf_json;
    if(!conf.exists()){
        conf_json.insert("IP","192.168.10.200");
        conf_json.insert("Port",8088);
        conf_json.insert("list_port",1138);
        conf_json.insert("list_ip","192.168.10.37");
        conf_json.insert("Muse_path","muse_file");
        conf_json.insert("log_path","logs");
        conf_json.insert("mysql_ip","127.0.0.1");
        conf_json.insert("mysql_port",3306);
        conf_json.insert("mysql_user","fengzi");
        conf_json.insert("mysql_password","fengzi");
        conf_json.insert("db_name","Return_visit_system");
        conf_json.insert("https_api_port",1148);
        conf_json.insert("his_ip","172.18.0.41");
        conf_json.insert("his_port",1521);
        conf_json.insert("his_user","zlhis");
        conf_json.insert("his_passwd","IM6IM6");
        conf_json.insert("his_database","orcl");

        conf.open(QFile::WriteOnly);
        conf.write(QJsonDocument(conf_json).toJson());
        conf.close();
    }else {
        conf.open(QFile::ReadOnly);
        QByteArray data=conf.readAll();
        conf_json=QJsonDocument::fromJson(data).object();
    }
    return conf_json;
}
