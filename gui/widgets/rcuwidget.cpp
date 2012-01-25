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

#include "rcuwidget.h"
#include "phosconstants.h"
#include "branchwidget.h"
#include <AckData.hpp>

using namespace PHOS;

RcuWidget::RcuWidget(RcuID rcuID, QWidget* parent)
: QGroupBox(parent),
  rcuID(rcuID)
{
  setupWidgets();

  readSettings();
}

RcuWidget::~RcuWidget()
{

}

void RcuWidget::setFecState(const FecID& id, uint_t newState)
{
  phosDcsLogging::Instance()->Logging("clickedds", LOG_LEVEL_INFO);
  return;
}


void RcuWidget::closeEvent(QCloseEvent* event)
{
  writeSettings();
  
  QWidget::closeEvent(event);
}


void RcuWidget::setupWidgets()
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


void RcuWidget::readSettings()
{
  QSettings settings("ALICE", "phos_dcs_2");
  QString rcustr(rcuID.toString().c_str());
  QString dcsName = settings.value( QString("rcuwidget/%1/dcsName").arg(rcustr) ).toString();

  //TODO: add action.
}

void RcuWidget::writeSettings()
{
  QString rcustr(rcuID.toString().c_str());
  QSettings settings("ALICE", "phos_dcs_2");
  settings.setValue(QString("rcuwidget/%1/dcsName").arg(rcustr),
                            "dcsXXXX");//TODO: replace with acctuall value when implemented;  
}


#include "rcuwidget.moc"