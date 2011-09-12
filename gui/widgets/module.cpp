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

#include "module.h"
#include "rcu.h"

module::module(Module_t module, QWidget* parent): QWidget(parent)
,_modId(module)
{
    setupWidgets();
}

void module::setupWidgets()
{
  rcu *r = 0;
  for(uint_t rc = 0; rc < RCUS_PER_MODULE; rc++)
  {
    Rcu_t tmpRcu(rc, _modId.getModuleId());
    r = new rcu(tmpRcu, this);
    r->setGeometry(10, 10+rc*(r->height()));
  }
  setFixedHeight(RCUS_PER_MODULE*r->height() + 20);
  setFixedWidth(RCUS_PER_MODULE*r->width() + 20);
}

#include "module.moc"