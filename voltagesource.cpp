#include "voltagesource.h"
#include <QDataStream>

VoltageSource::VoltageSource(QObject *parent) :
    QObject(parent)
{
    enable = false;
    tran_source = NONE;
    dc_enable = false;
    ac_enable = false;

}

void VoltageSource::prepareOption()
{
    option = "";

    if (dc_enable) {
        option += " DC ";
        option +=  dc;
    }

    if (ac_enable) {
        option += " AC ";
        option += ac;
        option += " ";
        option += acphase;
    }

    switch (tran_source) {
        case NONE:  break;
        case SIN:
                    option += " SIN(";
                    option += sin_vo;
                    option += " ";
                    option += sin_va;
                    option += " ";
                    option += sin_freq;
                    option += " ";
                    option += sin_td;
                    option += " ";
                    option += sin_theta;
                    option += ")";
                    break;
         case PULSE:
                    option += " PULSE(";
                    option += pulse_v1;
                    option += " ";
                    option += pulse_v2;
                    option += " ";
                    option += pulse_td;
                    option += " ";
                    option += pulse_tr;
                    option += " ";
                    option += pulse_tf;
                    option += " ";
                    option += pulse_pw;
                    option += " ";
                    option += pulse_per;
                    option += ")";
                    break;
        case EXP:
                    option += " EXP(";
                    option += exp_v1;
                    option += " ";
                    option += exp_v2;
                    option += " ";
                    option += exp_td1;
                    option += " ";
                    option += exp_tau1;
                    option += " ";
                    option += exp_td2;
                    option += " ";
                    option += exp_tau2;
                    option += ")";
                    break;
        case PWL:
                    option += " PWL(";
                    option += " ";
                    option += pwl;
                    option += ")";
                    break;
        case AM:
                    option += " AM(";
                    option += " ";
                    option += am_va;
                    option += " ";
                    option += am_vo;
                    option += " ";
                    option += am_mf;
                    option += " ";
                    option += am_fc;
                    option += " ";
                    option += am_td;
                    option += ")";
                    break;
        case FM:
                    option += " SFFM(";
                    option += " ";
                    option += fm_vo;
                    option += " ";
                    option += fm_va;
                    option += " ";
                    option += fm_fc;
                    option += " ";
                    option += fm_mdi;
                    option += " ";
                    option += fm_fs;
                    option += ")";
                    break;
        case TRNOISE:
                    option += " TRNOISE(";
                    option += " ";
                    option += noise_na;
                    option += " ";
                    option += noise_nt;
                    option += " ";
                    option += noise_nalpha;
                    option += " ";
                    option += noise_namp;
                    option += " ";
                    option += noise_rtsam;
                    option += " ";
                    option += noise_rtscapt;
                    option += " ";
                    option += noise_rtsemt;
                    option += ")";
                    break;


        default:
                    break;

    }


}

void VoltageSource::saveState(QDataStream* out)
{
    *out << line << enable << name << node1 << node2 << option;
    *out << dc_enable << ac_enable << dc << ac << acphase;
    *out << tran_source;
    *out << sin_vo << sin_va << sin_freq <<sin_td << sin_theta;
    *out << pulse_v1 << pulse_v2 << pulse_td << pulse_tr << pulse_tf << pulse_pw << pulse_per;
    *out << exp_v1 << exp_v2 << exp_td1 << exp_td2 << exp_tau1 << exp_tau2;
    *out << pwl;
    *out << am_va << am_vo << am_mf << am_fc << am_td;
    *out << fm_vo << fm_va << fm_fc << fm_mdi << fm_fs;
    *out << noise_na << noise_nt << noise_nalpha << noise_namp << noise_rtsam << noise_rtscapt << noise_rtsemt;


}

void VoltageSource::loadState(QDataStream* in)
{
    *in >> line >> enable >> name >> node1 >> node2 >> option;
    *in >> dc_enable >> ac_enable >> dc >> ac >> acphase;
    *in >> tran_source;
    *in >> sin_vo >> sin_va >> sin_freq >> sin_td >> sin_theta;
    *in >> pulse_v1 >> pulse_v2 >> pulse_td >> pulse_tr >> pulse_tf >> pulse_pw >> pulse_per;
    *in >> exp_v1 >> exp_v2 >> exp_td1 >> exp_td2 >> exp_tau1 >> exp_tau2;
    *in >> pwl;
    *in >> am_va >> am_vo >> am_mf >> am_fc >> am_td;
    *in >> fm_vo >> fm_va >> fm_fc >> fm_mdi >> fm_fs;
    *in >> noise_na >> noise_nt >> noise_nalpha >> noise_namp >> noise_rtsam >> noise_rtscapt >> noise_rtsemt;

}









