#ifndef PSS_H
#define PSS_H

#include <QObject>

class PSS : public QObject
{
    Q_OBJECT

public:
    bool enable;
    QString option;

    QString getControl();
    QString gfreq, tstab, oscnob, psspoints, harms, sciter, steadycoeff;
    bool uic;


    void saveState(QDataStream* out);
    void loadState(QDataStream* in);

public:
    explicit PSS(QObject *parent = 0);
    ~PSS();

signals:

public slots:
};

#endif // PSS_H
