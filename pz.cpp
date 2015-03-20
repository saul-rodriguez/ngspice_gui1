#include "pz.h"

PZ::PZ(QObject *parent) : QObject(parent)
{
    enable = false;
    option = "";
}

PZ::~PZ()
{

}

QString PZ::getControl()
{
    option = "pz ";
    option += n1;
    option += " ";
    option += n2;
    option += " ";
    option += n3;
    option += " ";
    option += n4;
    option += " ";
    option += type;
    option += " ";
    option += anal;
    option += "\n";

    return option;
}
