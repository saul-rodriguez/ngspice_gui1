#ifndef PZ_H
#define PZ_H

#include <QObject>

class PZ : public QObject
{
    Q_OBJECT
public:
    bool enable;
    QString option;

    QString n1,n2,n3,n4,type,anal;

    QString getControl();

public:
    explicit PZ(QObject *parent = 0);
    ~PZ();

signals:

public slots:
};

#endif // PZ_H
