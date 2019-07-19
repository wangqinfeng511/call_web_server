#ifndef OCIDATABASE_H
#define OCIDATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
class ocidatabase : public QObject
{
    Q_OBJECT
public:
    explicit ocidatabase(QObject *parent = nullptr);
    QSqlDatabase create_connect();
signals:

public slots:
};

#endif // OCIDATABASE_H
