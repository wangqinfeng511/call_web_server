#include "log.h"
#include <QDir>
#include<QFile>
#include <QJsonObject>
#include<QDateTime>
#include<QDebug>
#include "config.h"
log::log()
{
    config conf;
    conf_json=conf.read_config();
    QDir log_path(conf_json.value("log_path").toString());
    if(!log_path.exists()){
        log_path.mkpath("./");
    }
    log_dir=log_path.absolutePath();
}
void log::append_log(QString task_log){
    QDateTime time=QDateTime::currentDateTime();
    QString file_name=QString("%1.log").arg(time.toString("yyyy_MM_dd"));
    QString file_path=QString("%1/%2").arg(log_dir,file_name);
    QFile log_file(file_path);
    log_file.open(QIODevice::ReadWrite);
    log_file.seek(log_file.size());
    QString task_log_time=time.toString("hh:ss:mm");
    QString task_str=QString("%1  %2\n").arg(task_log_time,task_log);
    log_file.write(task_str.toLocal8Bit());
}
