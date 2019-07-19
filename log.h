#ifndef LOG_H
#define LOG_H
#include <QByteArray>
#include <QJsonObject>
class log
{
public:
    log(); 
    void append_log(QString task_log);
private:
    QJsonObject conf_json;
    QString log_dir;
};

#endif // LOG_H
