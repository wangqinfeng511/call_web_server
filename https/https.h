#ifndef HTTPS_H
#define HTTPS_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class https : public QTcpServer
{
    Q_OBJECT
public:
    https();
//    explicit https(QObject *parent = nullptr);
    void incomingConnection(qintptr socketDescriptor);
signals:

public slots:
};

class request_connect:public QTcpSocket{
      Q_OBJECT
    public:
        request_connect(int socketDesc,QTcpSocket *parent=NULL);
    private slots:
        void Read_data();
    signals:
};

#endif // HTTPS_H
