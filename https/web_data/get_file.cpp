#include "get_file.h"
#include "../web_base.h"
#include<QDebug>
#include<QString>
#include <QJsonObject>
#include <QJsonDocument>
#include "../../config.h"
#include <QDir>
#include <QFile>

get_file::get_file(web_base *parent) : web_base(parent)
{
}
QByteArray get_file::get(QString url,QString request_head){
    config conf;
    QJsonObject conf_json=conf.read_config();
    QString muse_path=conf_json.value("Muse_path").toString();
    QDir muse_dir(muse_path);
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
    QString file_name=parent_json.value("file_name").toString();
    if(file_name!=NULL){
        QFile file(QString("%1/%2").arg(muse_dir.absolutePath(),file_name));
        file.open(QIODevice::ReadOnly);
        int file_size=file.size();
        QByteArray buff;
        buff=file.readAll();
        QByteArray head;
        head+="HTTP/1.1 200 OK\r\n";
        head+="connection:close\r\n";
        head+="content-type: audio/wav\r\n";
        head+="status: 200\r\n";
        QString data="{'status','OK'}";
        QString head_length=QString("content-length: %1\r\n\r\n").arg(file_size);
        head+=head_length;
        head+=buff;
        return  head;
    }
};
