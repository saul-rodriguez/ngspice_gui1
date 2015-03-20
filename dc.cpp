#include "dc.h"

Dc::Dc(QObject *parent) :
    QObject(parent)
{
    enable = false;
    option = "";
}

QString Dc::getControl()
{

    option = "dc ";
    option += src1;
    option += " ";
    option += start1;
    option += " ";
    option += stop1;
    option += " ";
    option += step1;
    option += " ";
    option += start2;
    option += " ";
    option += stop2;
    option += " ";
    option += step2;
    option += "\n";

    return option;
}

