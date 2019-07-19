#ifndef IMAGE_H
#define IMAGE_H
#include "../web_base.h"
#include <QObject>
#include <QByteArray>
class image : public web_base
{
    Q_OBJECT
public:
    explicit image(web_base *parent = nullptr);
    QByteArray get(QString path,QString response);
signals:

public slots:
};

#endif // IMAGE_H
