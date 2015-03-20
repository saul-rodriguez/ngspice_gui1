#include "noise.h"

Noise::Noise(QObject *parent) :
    QObject(parent)
{
    enable = false;
    option = "";

}

QString Noise::getControl()
{

    option = "noise ";
    option += "v(";
    option += vout;

    if (vref.compare("")) {
        option += ",";
        option += vref;
    }
    option += ") ";
    option += src;
    option += " ";
    option += scale;
    option += " ";
    option += pts;
    option += " ";
    option += fstart;
    option += " ";
    option += fstop;
    option += " ";
    option += pts_per_sum;

    option += "\n";

    return option;

}
