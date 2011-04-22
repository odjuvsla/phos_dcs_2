#ifndef phos_dcs_2_H
#define phos_dcs_2_H

#include <QtCore/QObject>

class phos_dcs_2 : public QObject
{
Q_OBJECT
public:
    phos_dcs_2();
    virtual ~phos_dcs_2();
private slots:
    void output();
};

#endif // phos_dcs_2_H
