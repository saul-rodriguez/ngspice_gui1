#ifndef NOISE_H
#define NOISE_H

#include <QObject>

class Noise : public QObject
{
    Q_OBJECT

public:
    bool enable;
    QString option;

    QString vout,vref,src,scale,pts,fstart,fstop,pts_per_sum;

    QString getControl();

    void saveState(QDataStream* out);
    void loadState(QDataStream* in);

public:
    explicit Noise(QObject *parent = 0);

signals:

public slots:

};

#endif // NOISE_H
