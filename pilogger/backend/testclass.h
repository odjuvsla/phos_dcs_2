#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>

class testclass : public QObject
{
    Q_OBJECT
public:
    explicit testclass(QObject *parent = 0);

signals:

public slots:

};

#endif // TESTCLASS_H
