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

#include "branch.h"
#include "feecard.h"
#include <QFrame>
#include "QDebug"

branch::branch( BranchID branchId, QWidget* parent, Qt::WindowFlags f ) : QWidget ( parent, f )
,_branch(branchId)
,_feeCards(0)
,_frame()
,_label()
,_kWidth(CARDS_PER_BRANCH*15+20)
,_kHeight(100)
{
  setFixedSize(_kWidth, _kHeight);
  setupWidgets();
  setupConnections();
}

branch::~branch()
{
  
}

void branch::setupWidgets()
{
  _frame = new QFrame(this);
  _frame->setFrameShadow(QFrame::Raised);
  _frame->setFrameShape(QFrame::StyledPanel);
  _frame->setFixedSize(_kWidth, _kHeight);
  
  for(uint_t c = 0; c < CARDS_PER_BRANCH; c++)
  {
    FecID cardId(c+1, _branch.getBranchId(), _branch.getRcuId(), _branch.getModuleId());
    feeCard *card = new feeCard(cardId, this);
    if(_branch.getBranchId() == BRANCH_A)
    {
      card->setGeometry(10+c*15, 10);
    }
    if(_branch.getBranchId() == BRANCH_B)
    {
      card->setGeometry(_kWidth - c*15 - 25, 10);
    }
  }
}

void branch::setupConnections()
{
  
}


#include "branch.moc"