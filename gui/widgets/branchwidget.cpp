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
#include "branchwidget.h"

#include <QtGui>
#include "fecbutton.h"

BranchWidget::BranchWidget(BranchID branchId, QWidget* parent )
: QGroupBox ( parent ),
  branchID(branchId),
  fecButtons(0)

{
  setupWidgets();
  setupConnections();
}


void BranchWidget::setupWidgets()
{
  QHBoxLayout* mainLayout = new QHBoxLayout; 

  for(uint_t cIdx = 1; cIdx <= CARDS_PER_BRANCH; cIdx++)
  {
    FecID id(cIdx, branchID);
    FecButton* fecButton = new FecButton(id, this);
    mainLayout->addWidget(fecButton);
    fecButtons.append(fecButton);
  }
  setLayout(mainLayout);
}

void BranchWidget::setupConnections()
{
  
}


#include "branchwidget.moc"