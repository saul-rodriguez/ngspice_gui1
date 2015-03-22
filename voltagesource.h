#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H

#include <QObject>

#define NONE 0
#define SIN 1
#define PULSE 2
#define EXP 3
#define PWL 4
#define FM 5
#define AM 6
#define TRNOISE 7


class VoltageSource : public QObject
{
    Q_OBJECT
public:
    explicit VoltageSource(QObject *parent = 0);

public:
    int line; //Line in the spice file
    bool enable; // if TRUE the original values will be overrided

    QString name;
    QString node1;
    QString node2;

    QString option;

    bool dc_enable, ac_enable;
    QString dc,ac,acphase;

    qint32 tran_source;
    QString sin_vo,sin_va,sin_freq,sin_td,sin_theta;
    QString pulse_v1,pulse_v2,pulse_td,pulse_tr,pulse_tf,pulse_pw,pulse_per;
    QString exp_v1, exp_v2, exp_td1, exp_td2, exp_tau1, exp_tau2;
    QString pwl;
    QString am_va,am_vo,am_mf,am_fc,am_td;
    QString fm_vo,fm_va,fm_fc,fm_mdi,fm_fs;
    QString noise_na,noise_nt,noise_nalpha,noise_namp,noise_rtsam,noise_rtscapt,noise_rtsemt;

    void prepareOption();

    void saveState(QDataStream* out);
    void loadState(QDataStream* in);

signals:

public slots:

};

#endif // VOLTAGESOURCE_H
