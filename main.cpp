#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "socket_server.h"
#include <heartbeat.h>
#include <qthread.h>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "config.h"
#include "https/https.h"
#include <QJsonObject>
#include "database.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    config conf;
    QJsonObject config_json=conf.read_config();
    socket_server call_service;
    int call_service_port=config_json.value("list_port").toInt();
    if(call_service.listen(QHostAddress::Any,call_service_port)){

    }else {
        qDebug()<<"电话交换监听错误！";
    };
    https https_service;
    int  web_port=config_json.value("https_api_port").toInt();
    if(https_service.listen(QHostAddress::Any,web_port)){

    }else {
        qDebug()<<"web"<<config_json.value("https_api_port").toInt()<<"ERROR!";
    }
    heartbeat start_heartbeat;
    QThread *task_hearbeat= new QThread();
    start_heartbeat.moveToThread(task_hearbeat);
    QObject::connect(&call_service,SIGNAL(send_token(QString)),&start_heartbeat,SLOT(set_token(QString)));
    task_hearbeat->start();
//    database db;
//    db.select_call_record("2019-04-29","2019-04-31","10001","all");
    return app.exec();
}
