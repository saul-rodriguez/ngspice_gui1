#include "noise.h"
#include <QDataStream>

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

void Noise::saveState(QDataStream* out)
{
    *out << enable << vout << vref << src << scale << pts << fstart << fstop << pts_per_sum << option;
}

void Noise::loadState(QDataStream* in)
{
    *in >> enable >> vout >> vref >> src >> scale >> pts >> fstart >> fstop >> pts_per_sum >> option;
}
