#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <heartbeat.h>
#include <qthread.h>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "https/https.h"
#include <QJsonObject>
#include "web_router.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    https https_service;
    if(https_service.listen(QHostAddress::Any,1148)){

    }else {
        qDebug()<<"web"<<1148<<"ERROR!";
    }
//    web_router router;
//    router.get("/");
    return app.exec();
}
