#include "dc.h"
#include <QDataStream>

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
    option += src2;
    option += " ";
    option += start2;
    option += " ";
    option += stop2;
    option += " ";
    option += step2;
    option += "\n";

    return option;
}

void Dc::saveState(QDataStream* out)
{
    *out << enable << src1 << start1 << stop1 << step1 << src2 << start2 << stop2 << step2 << option;

}

void Dc::loadState(QDataStream* in)
{
    *in >> enable >> src1 >> start1 >> stop1 >> step1 >> src2 >> start2 >> stop2 >> step2 >> option;
}
