#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QJsonArray>
class database : public QObject
{
    Q_OBJECT
public:
    explicit database(QObject *parent = nullptr);
    QSqlDatabase create_db_connect();
    QJsonObject insert_ccall_record(QJsonObject data);
    QJsonArray select_call_record(QString start_time, QString end_time,QString scall,QString dcall);
    //user
    QJsonArray select_users();
    QJsonObject select_user(int user_id);
    QJsonObject add_user(QString user,QString passwd);
    QJsonObject delete_user(int user_id);
    QJsonObject update_passwd(int user_id,QString passwd);
    QJsonObject set_role(int user_id,int role_id);
    QJsonObject login(QString user,QString passwd);
    //role
    QJsonArray select_role();
signals:

public slots:
};

#endif // DATABASE_H
