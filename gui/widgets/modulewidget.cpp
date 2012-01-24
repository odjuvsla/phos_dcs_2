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

#include "modulewidget.h"
#include "rcuwidget.h"

ModuleWidget::ModuleWidget(ModuleID module, QWidget* parent)
: QWidget(parent)
  ,modID(module)
{
  setupWidgets();
}

void ModuleWidget::setupWidgets()
{
  
  QVBoxLayout* mainLayout = new QVBoxLayout;
  for(uint_t rIdx = 0; rIdx < RCUS_PER_MODULE; rIdx++)
  {
    RcuID rcuID(rIdx, modID);
    RcuWidget * r = new RcuWidget(rcuID, this);
    mainLayout->addWidget(r);
  }
  setLayout(mainLayout);
}

#include "modulewidget.moc"
