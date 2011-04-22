#include "phos_dcs_2.h"

#include <QTimer>
#include <iostream>

phos_dcs_2::phos_dcs_2()
{
    QTimer* timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), SLOT(output()) );
    timer->start( 1000 );
}

phos_dcs_2::~phos_dcs_2()
{}

void phos_dcs_2::output()
{
    std::cout << "Hello World!" << std::endl;
}

#include "phos_dcs_2.moc"
