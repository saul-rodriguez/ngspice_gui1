#ifndef SPICEFILE_H
#define SPICEFILE_H

#include <QObject>
#include <QStringList>

#include "voltagesource.h"
#include "currentsource.h"

#define NUM_SOURCES 40
#define NUM_LINES 1024

class SpiceFile : public QObject
{
    Q_OBJECT

public:
    QStringList fileLines;
    int fileSize; //number of lines

    QString control;

public:
    VoltageSource source[NUM_SOURCES];
    qint32 SourceNum;

    //VoltageSource vsource[NUM_SOURCES];
    //int VoltageSourceNum;

    //CurrentSource isource[NUM_SOURCES];
    //VoltageSource isource[NUM_SOURCES];
    //int CurrentSourceNum;

    //int lines[NUM_LINES][2];

public:
    explicit SpiceFile(QObject *parent = 0);

    void readSpice(QString name);
    void writeSpice(QString name);

signals:

public slots:

};

#endif // SPICEFILE_H
