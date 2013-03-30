/*
    Library for controlling and configuring the electronics for the PHOS
    detector at the ALICE Experiment
    Copyright (C) 2011  Oystein Djuvsland <oystein.djuvsland@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "moduletabs.h"
#include <QTabWidget>
#include <iostream>

#include "phosconstants.h"
using namespace PHOS;

#include "modulewidget.h"
#include "feetester.h"

ModuleTabs::ModuleTabs(QWidget *parent)
: QTabWidget(parent)
{
  
  for(uint_t m = 0; m < PHOS_MODS; m++)
  {
    QString moduleName = QString("Module %1").arg(m);
    ModuleID mod(m);

    ModuleWidget * newMod = new ModuleWidget(mod, this);
    addTab(newMod, moduleName);
  }
  FeeTester *tester = new FeeTester(this);
  addTab(tester, "FEE Tester");
}

ModuleTabs::~ModuleTabs()
{

}

#include "moduletabs.moc"