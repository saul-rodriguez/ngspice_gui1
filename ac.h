#ifndef AC_H
#define AC_H

#include <QObject>

class Ac : public QObject
{
    Q_OBJECT

public:
    bool enable;
    QString option;

    QString startFrec;
    QString stopFrec;
    QString step;
    QString scale;

public:
    explicit Ac(QObject *parent = 0);

    QString getControl();

    void saveState(QDataStream* out);
    void loadState(QDataStream* in);

signals:

public slots:

};

#endif // AC_H
