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
#include "branchwidget.h"

using namespace phosConstants;

rcu::rcu(RcuID rcuID, QWidget* parent)
: QGroupBox(parent),
  rcuID(rcuID)
{
  setupWidgets();
}

rcu::~rcu()
{

}

void rcu::setupWidgets()
{
  QHBoxLayout* mainLayout = new QHBoxLayout;

  QVBoxLayout* actionsLayout = new QVBoxLayout;
  mainLayout->addLayout(actionsLayout);

  QLabel* label = new QLabel(QString("RCU_%1").arg(rcuID.getRcuId()), this);
  label->setAlignment(Qt::AlignLeft);
  actionsLayout->addWidget(label);
  actionsLayout->addWidget(new QPushButton("Update", this));
  actionsLayout->addWidget(new QPushButton("All On", this));
  actionsLayout->addWidget(new QPushButton("All Off", this));
  actionsLayout->addStretch();

  BranchID baID(BRANCH_A, rcuID);
  BranchWidget *ba = new BranchWidget(baID, this);
  mainLayout->addWidget(ba);
  

  BranchID bbID(BRANCH_B, rcuID);
  BranchWidget *bb = new BranchWidget(bbID, this);
  mainLayout->addWidget(bb);
  
  setLayout(mainLayout);
}

#include "rcu.moc"