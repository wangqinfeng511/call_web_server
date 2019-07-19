#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QJsonObject>
class config : public QObject
{
    Q_OBJECT
public:
    explicit config(QObject *parent = nullptr);
    QJsonObject read_config();
signals:

public slots:
};

#endif // CONFIG_H
