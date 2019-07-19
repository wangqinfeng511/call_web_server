#include "web_base.h"
#include <QString>
web_base::web_base(QObject *parent) : QObject(parent)
{

}
QByteArray web_base::get(QString path,QString request_head){
    QByteArray head;
    head+="HTTP/1.1 400 OK\r\n";
    head+="content-type: text/html; charset=utf-8\r\n";
    head+="status: 400\r\n\r\n";
    return  head;
}
