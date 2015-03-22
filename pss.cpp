#include "pss.h"
#include <QDataStream>

PSS::PSS(QObject *parent) : QObject(parent)
{
    enable = false;
    option = "";
    uic = false;
}

PSS::~PSS()
{

}

QString PSS::getControl()
{
    option = "pss ";
    option += gfreq;
    option += " ";
    option += tstab;
    option += " ";
    option += oscnob;
    option += " ";
    option += psspoints;
    option += " ";
    option += harms;
    option += " ";
    option += sciter;
    option += " ";
    option += steadycoeff;

    if (uic) {
        option += "uic";
    }

    option += "\n";

    return option;

}

void PSS::saveState(QDataStream* out)
{
    *out << enable << gfreq << tstab << oscnob << psspoints << harms << sciter << steadycoeff << uic << option;
}

void PSS::loadState(QDataStream* in)
{
    *in  >> enable >> gfreq >> tstab >> oscnob >> psspoints >> harms >> sciter >> steadycoeff >> uic >> option;
}
