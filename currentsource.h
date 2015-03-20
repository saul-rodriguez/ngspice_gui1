#ifndef CURRENTSOURCE_H
#define CURRENTSOURCE_H

#include <QObject>

class CurrentSource : public QObject
{
    Q_OBJECT
public:
    explicit CurrentSource(QObject *parent = 0);

public:
    int line; //Line in the spice file
    bool enable; // if TRUE the original values will be overrided

    QString name;
    QString node1;
    QString node2;

signals:

public slots:

};

#endif // CURRENTSOURCE_H
