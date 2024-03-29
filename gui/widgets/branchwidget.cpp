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
#include "rcuwidget.h"

#include "phosconstants.h"
using namespace PHOS;

/** Constructor */
BranchWidget::BranchWidget(BranchID id, QWidget* parent )
: QGroupBox ( parent ),
  branchID(id),
  fecButtons(0)

{
  if( BRANCH_A == branchID.getBranchId() )
    setTitle("Branch A");
  else if( BRANCH_B == branchID.getBranchId() )
    setTitle("Branch B");

  
  setupWidgets();
  setupConnections();
}

/** returns pointer to FecButton,
 *
 * BranchWidget instance retains ownership of FecButton pointed to.
 * Does NOT test validity of branch, rcu, and mod of fecID.
 */
FecButton* BranchWidget::getFecButton(const FecID& fecID)
{
  return fecButtons.at(fecID.getFecId() - 1 );
}

/** returns "vector" of fecbuttons.
 *
 * BranchWidget retains ownership of vector and FecButtons pointers point to.
 */
QVector< FecButton* >& BranchWidget::getFecButtons()
{
  return fecButtons;
}


void BranchWidget::setAll(FecStatus status, const QString& message)
{
  foreach(FecButton* button, fecButtons) {
    button->setStatus(status, message);
  }
}


// /** Slot to be used by FecButton instances to request toggle states on/off
//  * , will set button to Waiting and emit setFecState signal.
//  */
// void BranchWidget::fecButtonClicked()
// {
//   FecButton* fecButton = qobject_cast<FecButton *>(sender());
//   if(fecButton->getStatus() == FEC_ON){
//     fecButton->setStatus(FEC_UNKNOWN, "sent request to toggle to Off");
//     emit setFecState( fecButton->getFecID(), FEC_OFF );
//   }
//   else if(fecButton->getStatus() == FEC_OFF) {
//     fecButton->setStatus(FEC_UNKNOWN, "sent request to toggle to On");
//     emit setFecState( fecButton->getFecID(), FEC_ON );
//   }
//   else {
//     phosDcsLogging::Instance()->Logging("fec button should not be clickable if other state then On/Off",
// 					LOG_LEVEL_ERROR, __FILE__, __LINE__);
//     exit(-1);
//   }
// }


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
//   foreach(const FecButton* button, fecButtons) {
//     connect(button, SIGNAL(clicked()), this, SLOT(fecButtonClicked()));
//   };
}


#include "branchwidget.moc"
