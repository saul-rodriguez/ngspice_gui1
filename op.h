#ifndef OP_H
#define OP_H

#include <QObject>

class Op : public QObject
{
    Q_OBJECT

public:
    bool enable;
    QString option;

public:
    explicit Op(QObject *parent = 0);
    ~Op();

signals:

public slots:
};

#endif // OP_H
