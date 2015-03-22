#include "pz.h"
#include <QDataStream>

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

void PZ::saveState(QDataStream* out)
{
    *out << enable << n1 << n2 << n3 << n4 << type << anal << option;
}

void PZ::loadState(QDataStream* in)
{
    *in >> enable >> n1 >> n2 >> n3 >> n4 >> type >> anal >> option;
}
