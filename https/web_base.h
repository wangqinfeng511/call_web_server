#ifndef WEB_BASE_H
#define WEB_BASE_H
#include <QObject>
#include <QByteArray>
class web_base :public QObject{

   Q_OBJECT
public:
    web_base(QObject *parent=nullptr);
    virtual QByteArray get(QString path,QString request_head);
};

#endif // WEB_BASE_H
