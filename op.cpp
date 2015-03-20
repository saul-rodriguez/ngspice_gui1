#include "op.h"

Op::Op(QObject *parent) : QObject(parent)
{
    enable = 0;
    option = "op\n";

}

Op::~Op()
{

}

