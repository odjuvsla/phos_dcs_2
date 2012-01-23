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

#ifndef BRANCH_H
#define BRANCH_H

class FecButton;

#include <QtGui>
#include <idtypes.h>

class BranchWidget : public QGroupBox
{

  Q_OBJECT
    
public:
    /** Constructor */
    BranchWidget(BranchID branchId, QWidget* parent = 0);

    
private:

  /** Setup the internal widgets */
  void setupWidgets();
  
  /** Setup the slot connections */
  void setupConnections();
  
  /** Branch id */
  BranchID branchID;
  
  /** The FECs */
  QVector<FecButton*> fecButtons;
  
  /** not allowed */
  BranchWidget();
  BranchWidget(const BranchWidget& );
  BranchWidget operator=(const BranchWidget&);
  
};

#endif // BRANCH_H
