#include "voltagesource.h"

VoltageSource::VoltageSource(QObject *parent) :
    QObject(parent)
{
    enable = false;
    tran_source = NONE;
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









