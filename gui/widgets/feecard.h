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

#ifndef FECCARD_H
#define FECCARD_H

#include <QPushButton>
#include "phosdcstypes.h"


class feeCard : public QPushButton
{
  Q_OBJECT
public:
  
  /** Constructor must pass FEC card definition */
  explicit feeCard (FecID card,  QWidget* parent = 0);
  
  virtual ~feeCard();
  
  void setGeometry(int x, int y) { QPushButton::setGeometry(x, y, _kWidth, _kHeight);}
  
private:

  /** FEC definition */
  FecID fFecId;
  
  /** Default constructor, prohibited */
  feeCard();
  
  const int _kWidth;
  const int _kHeight;
  
};

#endif // FECCARD_H
