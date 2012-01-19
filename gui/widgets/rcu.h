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

#ifndef RCU_H
#define RCU_H

#include <QtGui/qwidget.h>
#include "idtypes.h"


class rcu : public QWidget
{
  Q_OBJECT
public:
  
  /** Constructor must pass RCU definition */
  explicit rcu (RcuID card,  QWidget* parent = 0);
  
  virtual ~rcu();
  
  void setGeometry(int x, int y) { QWidget::setGeometry(x, y, width(), height());}
  
private:

  /** RCU definition */
  RcuID _rcuId;
  
  /** Default constructor, prohibited */
  rcu();
    void setupWidgets();

};

#endif // RCU_H
