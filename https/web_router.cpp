#include "web_router.h"
#include "web_base.h"
#include <QDebug>
#include "./web_data/call_records.h"
#include "./web_data/image.h"
#include "./web_data/get_file.h"
#include "./web_data/phone_call.h"
#include "./web_data/user.h"
#include "./web_data/role.h"
web_router::web_router(QObject *parent) : QObject(parent)
{
// /user
    user *get_user=new user();
    get_user->setObjectName("/user");
    web_path_list.append(get_user);
// /role
    role *get_role=new role();
    get_role->setObjectName("/role");
    web_path_list.append(get_role);
// /call_records
    call_records *call_records_addr=new call_records();
    call_records_addr->setObjectName("/call_records");
    web_path_list.append(call_records_addr);

//    /favicon.ico
    image *get_image=new image();
    get_image->setObjectName("/favicon.ico");
    web_path_list.append(get_image);
//  /get_file
    get_file *getfile=new get_file();
    getfile->setObjectName("/get_file");
    web_path_list.append(getfile);
// /phone_call
    phone_call *phonecall=new phone_call();
    phonecall->setObjectName("/phone_call");
    web_path_list.append(phonecall);
}
QByteArray web_router::respnse(QString path,QString method,QString request_head){
//    qDebug()<<path<<method;
    for(int i=0;i<web_path_list.length();i++){
        if(web_path_list[i]->objectName()==path){
            return  web_path_list[i]->get(path,request_head);

//            QByteArray
//            connect(web_path_list[i],SIGNAL(send_data(QByteArray)),this,SLOT(write_data(QByteArray)));
        }else {
            qDebug()<<"url not:"<<path;
            //return error
        }
    }
//    cache-control: max-age=86400
//    content-encoding: gzip
//    content-type: application/javascript; charset=utf-8
//    date: Mon, 29 Apr 2019 03:36:05 GMT
//    etag: W/"5a5dbc83-a69"
//    expires: Tue, 30 Apr 2019 03:36:05 GMT
//    last-modified: Tue, 16 Jan 2018 08:49:07 GMT
//    server: openresty
//    status: 200
//    vary: Accept-Encoding
}
