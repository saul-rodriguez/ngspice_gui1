#include "op.h"
#include <QDataStream>

Op::Op(QObject *parent) : QObject(parent)
{
    enable = 0;
    option = "op\n";

}

Op::~Op()
{

}

void Op::saveState(QDataStream* out)
{
    *out << enable << option;
}

void Op::loadState(QDataStream* in)
{
    *in >> enable >> option;
}
