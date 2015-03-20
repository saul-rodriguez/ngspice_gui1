#include "tran.h"

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
