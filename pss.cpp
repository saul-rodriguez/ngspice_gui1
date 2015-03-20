#include "pss.h"

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

