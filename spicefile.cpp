#include "spicefile.h"
#include <QFile>
#include <QTextStream>


SpiceFile::SpiceFile(QObject *parent) :
    QObject(parent)
{
    //VoltageSourceNum = 0;
    //CurrentSourceNum = 0;
    SourceNum = 0;
    control = "\n";
}

void SpiceFile::readSpice(QString name)
{
    QFile file(name);

    if(!file.open(QIODevice::ReadOnly)) {
            qDebug("error opening file");
    }

    //Read file and parse it
    QTextStream in(&file);

    QString db = in.readAll();
    //fileLines = new QStringList(db.split(QRegExp("\n")));
    //fileSize = fileLines->length();

    fileLines = db.split(QRegExp("\n"));
    fileSize = fileLines.length();

    //Extract V and I sources
    QStringList fields;
    QString subString;
    QChar *data;

    //VoltageSourceNum = 0;
    //CurrentSourceNum = 0;
    SourceNum = 0;

    for (int i=0; i<fileSize; i++) {
        //fields = (*fileLines)[i].split(QRegExp("\\s+"));
        fields = fileLines[i].split(QRegExp("\\s+"));

         data = fields[0].data();
         /*
        //Voltage Source
        if(data[0] == 'V' or data[0] == 'v') {
        //if(fields[0].contains("V", Qt::CaseInsensitive)) {
            if (VoltageSourceNum < NUM_SOURCES) {
                vsource[VoltageSourceNum].line = i; // Save line number
                vsource[VoltageSourceNum].name = fields[0];
                vsource[VoltageSourceNum].node1 = fields[1];
                vsource[VoltageSourceNum].node2 = fields[2];
                VoltageSourceNum++;
            }
        };

        if(data[0] == 'I' or data[0] == 'i') {
        //if(fields[0].contains("I", Qt::CaseInsensitive)) {
            if (CurrentSourceNum < NUM_SOURCES) {
                isource[CurrentSourceNum].line = i;
                isource[CurrentSourceNum].name = fields[0];
                isource[CurrentSourceNum].node1 = fields[1];
                isource[CurrentSourceNum].node2 = fields[2];
                CurrentSourceNum++;
            }
        };*/

        if(data[0] == 'V' || data[0] == 'v' || data[0] == 'I' || data[0] == 'i') {
        //if(fields[0].contains("V", Qt::CaseInsensitive)) {
            if (SourceNum < NUM_SOURCES) {
                source[SourceNum].line = i; // Save line number
                source[SourceNum].name = fields[0];
                source[SourceNum].node1 = fields[1];
                source[SourceNum].node2 = fields[2];
                SourceNum++;
            }
        };

        QString end = ".end";
        int comp = QString::compare(fileLines[i], end, Qt::CaseInsensitive);
        if (!comp) {
            fileLines[i] = "";
        }
    }

    file.close();
}

void SpiceFile::writeSpice(QString name)
{
    QFile fout(name);

    if(!fout.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug("error opening writing file");
    }

    QTextStream stream( &fout);

    QString aux;

    //int j;
    int flag = 0;
    for (int i=0; i<(fileSize); i++) { //Last line (.end) is printed later!

        /*
        //Replace voltage sources with customized analysis parameters
        for (j=0; j<VoltageSourceNum; j++) {
            if (vsource[j].line == i && vsource[j].enable == true) {
                stream << vsource[j].name
                       << " " << vsource[j].node1
                       << " " << vsource[j].node2
                       << "\n";
                flag = 1;
                break;
            }
        }

        if (flag) {
            flag = 0;
            continue;
        }

        //Replace current sources with customized analysis parameters
        for (int j=0; j<CurrentSourceNum; j++) {
            if (isource[j].line == i && isource[j].enable == true) {
                stream << isource[j].name
                       << " " << isource[j].node1
                       << " " << isource[j].node2
                       << "\n";
                flag = 1;
                break;
            }
        }

        if (flag) {
            flag = 0;
            continue;
        }
        */
        for (int j=0; j<SourceNum; j++) {
            if (source[j].line == i && source[j].enable == true) {
                stream << source[j].name
                       << " " << source[j].node1
                       << " " << source[j].node2
                       << " " << source[j].option
                       << "\n";
                flag = 1;
                break;
            }
        }

        if (flag) {
            flag = 0;
            continue;
        }

        if (QString::compare(fileLines[i],"\n")) {
            //continue;
        }
        stream << fileLines[i] << '\n';

    }

    stream << "* Simulation Section *\n";
    stream << control;

    stream << ".end\n";

    fout.close();
}

