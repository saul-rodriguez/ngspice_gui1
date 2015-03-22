#include "tran.h"
#include <QDataStream>

Tran::Tran(QObject *parent) :
    QObject(parent)
{
    enable = false;
    option = "";
    uic = false;
}

QString Tran::getControl()
{
    option = "tran ";
    option += step;
    option += " ";
    option += stop;
    option += " ";
    option += start;
    option += " ";
    option += max;
    option += " ";

    if (uic) {
        option += "uic";
    }

    option += "\n";

    return option;
}

void Tran::saveState(QDataStream* out)
{
    *out << enable << step << stop << start << max << uic << option;
}
void Tran::loadState(QDataStream* in)
{
    *in >> enable >> step >> stop >> start >> max >> uic >> option;
}
