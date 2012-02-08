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
  idLabel(0),
  dcsNameEdit(0),
  dcsNameLabel(0),
  dcsNameStack(0),
  connectButton(0),
  updateButton(0),
  connectUpdateStack(0),
  menuButton(0),
  branchA(0),
  branchB(0),
  menu(0),
  disconnectAct(0),
  allOnAct(0),
  allOffAct(0),
  rcuID(rcuID),
  dcsInterface(0)
{
  dcsInterface = new PhosDcsInterface(rcuID);
  
  setupActions();
  setupWidgets();
  setupConnections();
  setupLayout();

  readSettings();
}

RcuWidget::~RcuWidget()
{

}

void RcuWidget::setFecStatus(const FecID& fecID, PHOS::FecStatus newStatus, const QString& message)
{
  if(BRANCH_A == fecID.getBranchId())
    branchA->getFecButton(fecID)->setStatus(newStatus, message);
  else
    branchB->getFecButton(fecID)->setStatus(newStatus, message);
}

void RcuWidget::connectDcs(QString dcsName)
{
  dcsNameEdit->setEnabled(false);
  connectButton->setEnabled(false);

  int errorCode = 1;
  if(dcsName.size() > 0 )
    errorCode = dcsInterface->connect(dcsName);
  else
    errorCode = dcsInterface->connect(dcsNameEdit->text());

  if( ! errorCode ) { // if success 
    dcsNameLabel->setText(dcsNameEdit->text());
    dcsNameStack->setCurrentIndex(1);
    connectUpdateStack->setCurrentIndex(1);
  }
  else { // if error 
    dcsNameEdit->setEnabled(true);
    connectButton->setEnabled(true);
  }

}

void RcuWidget::disconnectDcs()
{
  phosDcsLogging::Instance()->Logging("RcuWidget::disconnectDcs not implemented", LOG_LEVEL_ERROR);
}

void RcuWidget::allOn()
{
  phosDcsLogging::Instance()->Logging("RcuWidget::allOn not implemented", LOG_LEVEL_ERROR);
  //TODO: implement slot
}

void RcuWidget::allOff()
{
  phosDcsLogging::Instance()->Logging("RcuWidget::allOff not implemented", LOG_LEVEL_ERROR);
  //TODO: implement slot
}

void RcuWidget::update()
{
  //phosDcsLogging::Instance()->Logging("RcuWidget::update not implemented", LOG_LEVEL_ERROR);
  dcsInterface->updateActiveFec();
}

void RcuWidget::closeEvent(QCloseEvent* event)
{
  writeSettings();
  
  //QWidget::closeEvent(event);
}

void RcuWidget::setupActions()
{
  disconnectAct = new QAction("&Disconnect", this);
  allOnAct = new QAction("All &On", this);
  allOffAct = new QAction("All O&ff", this);

  menu = new QMenu("Menu", this);
  menu->addAction(allOnAct);
  menu->addAction(allOffAct);
  menu->addAction(disconnectAct);
}

void RcuWidget::setupWidgets()
{
  idLabel = new QLabel(QString("RCU_%1").arg(rcuID.getRcuId()), this);
  dcsNameEdit = new QLineEdit("dcsXXXX", this);
  dcsNameLabel = new QLabel(this);
  dcsNameStack = new QStackedWidget(this);
  dcsNameStack->addWidget(dcsNameEdit);
  dcsNameStack->addWidget(dcsNameLabel);

  connectButton = new QPushButton("&Connect", this);
  updateButton = new QPushButton("&Update", this);
  connectUpdateStack = new QStackedWidget(this);
  connectUpdateStack->addWidget(connectButton);
  connectUpdateStack->addWidget(updateButton);
  
  menuButton = new QPushButton("More...", this);
  menuButton->setMenu(menu);
  menuButton->setEnabled(false);

  branchA = new BranchWidget(BranchID(BRANCH_A, rcuID), this);
  branchB = new BranchWidget(BranchID(BRANCH_B, rcuID), this);;

}

void RcuWidget::setupConnections()
{
  // own buttons / actions
  connect(connectButton, SIGNAL(clicked()), this, SLOT(connectDcs()));
  connect(updateButton, SIGNAL(clicked()), this, SLOT(update()));
  connect(disconnectAct, SIGNAL(triggered()), this, SLOT(disconnectDcs()));
  connect(allOnAct, SIGNAL(triggered()), this, SLOT(allOn()));
  connect(allOffAct, SIGNAL(triggered()), this, SLOT(allOff()));

  // DCS interface
  connect(dcsInterface, SIGNAL(updatedFecStatus(FecID,PHOS::FecStatus,QString)),
	  this, SLOT(setFecStatus(FecID,PHOS::FecStatus,QString)));

  // FEC, TRUs ...
  foreach(FecButton* button, branchA->getFecButtons()) {
    connect(button, SIGNAL(requestFecStatus(FecID, PHOS::FecStatus)),
	    dcsInterface, SLOT(turnOnOffFec(FecID,PHOS::FecStatus)));
  }
  foreach(FecButton* button, branchB->getFecButtons()) {
    connect(button, SIGNAL(requestFecStatus(FecID, PHOS::FecStatus)),
	    dcsInterface, SLOT(turnOnOffFec(FecID,PHOS::FecStatus)));
  }
  
}


void RcuWidget::setupLayout()
{
  QHBoxLayout* mainLayout = new QHBoxLayout;
  QVBoxLayout* leftLayout = new QVBoxLayout;
  QHBoxLayout* labelLayout = new QHBoxLayout;

  mainLayout->addLayout(leftLayout);
  mainLayout->addWidget(branchA);
  mainLayout->addWidget(branchB);

  leftLayout->addLayout(labelLayout);
  leftLayout->addWidget(connectUpdateStack);
  leftLayout->addWidget(menuButton);
  leftLayout->addStretch();

  labelLayout->addWidget(idLabel);
  labelLayout->addStretch();
  labelLayout->addWidget(dcsNameStack);

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