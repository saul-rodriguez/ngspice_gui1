#include "currentsource.h"

CurrentSource::CurrentSource(QObject *parent) :
    QObject(parent)
{
    enable = false;
}
