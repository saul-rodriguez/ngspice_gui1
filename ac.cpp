#include "ac.h"

Ac::Ac(QObject *parent) :
    QObject(parent)
{
    enable = 0;
    option = "ac lin 1 1 10k\n";
}

QString Ac::getControl()
{

    option = "ac ";
    option += scale;
    option += " ";
    option += step;
    option += " ";
    option += startFrec;
    option += " ";
    option += stopFrec;
    option += "\n";

    return option;

}

