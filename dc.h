#ifndef DC_H
#define DC_H

#include <QObject>

class Dc : public QObject
{
    Q_OBJECT

public:
    bool enable;
    QString option;

    QString src1;
    QString start1;
    QString stop1;
    QString step1;

    QString src2;
    QString start2;
    QString stop2;
    QString step2;

    QString getControl();

    void saveState(QDataStream* out);
    void loadState(QDataStream* in);

public:
    explicit Dc(QObject *parent = 0);

signals:

public slots:

};

#endif // DC_H
