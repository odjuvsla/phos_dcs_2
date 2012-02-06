/*
    Library for controlling and configuring the electronics for the PHOS
    detector at the ALICE Experiment
    Copyright (C) 2011  Oystein Djuvsland <oystein.djuvsland@gmail.com>,
			Henrik Qvigstad <henrik.qvigstad@cern.ch>

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
#include "idtypes.h"
#include "phosconstants.h"
#include <QDate>


class FecButton : public QPushButton
{
  Q_OBJECT
public:
  /** Constructor must pass FEC card definition */
  FecButton (FecID fecID, QWidget* parent = 0);

  virtual QSize sizeHint() const; 
  virtual QSize minimumSizeHint() const;
  virtual QSize maximumSizeHint() const;

  const FecID& getFecID() {return fecID;}

  PHOS::FecStatus GetStatus() const { return status; }

public slots:
  void SetStatus(PHOS::FecStatus newStatus, const QString& message);
  
private:

  /** FEC definition */
  FecID fecID;
  PHOS::FecStatus status;

  
  /** Default constructor, prohibited */
  //FecButton();
    
};

#endif // FECCARD_H
