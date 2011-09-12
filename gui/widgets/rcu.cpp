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

#include "rcu.h"
#include "phosconstants.h"
#include "branch.h"

using namespace phosConstants;

rcu::rcu(Rcu_t card, QWidget* parent): QWidget(parent) 
,_rcuId(card)
{
  setupWidgets();
}

rcu::~rcu()
{

}

void rcu::setupWidgets()
{
  Branch_t branchB(BRANCH_B,0,0);
  branch *bb = new branch(branchB, this);
  bb->setGeometry(10, 10);
  
  Branch_t branchA(BRANCH_A, 0, 0);
  branch *ba = new branch(branchA, this);
  ba->setGeometry(bb->x() + bb->width() + 10, bb->y());
  
  setFixedHeight(bb->height()+20);
  setFixedWidth(bb->width()*2 + 20);
}

#include "rcu.moc"