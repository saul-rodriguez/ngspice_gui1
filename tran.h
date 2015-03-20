#ifndef TRAN_H
#define TRAN_H

#include <QObject>

class Tran : public QObject
{
    Q_OBJECT
public:
    bool enable;
    QString option;

    QString step;
    QString stop;
    QString start;
    QString max;
    bool uic;

    QString getControl();

public:
    explicit Tran(QObject *parent = 0);

signals:

public slots:

};

#endif // TRAN_H
