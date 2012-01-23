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

#include "fecbutton.h"

FecButton::FecButton (FecID fecID, QWidget* parent)
: QPushButton ( parent ),
  fecID(fecID)
{
  QString hexId;
  hexId = hexId.setNum(fecID.getFecId(), 16);
  setText(hexId.toUpper());
}

QSize FecButton::sizeHint() const
{
  return QSize(16, 96);
}

QSize FecButton::minimumSizeHint() const
{
  return QSize(16, 64);
}

QSize FecButton::maximumSizeHint() const
{
  return QSize(20, 128);
}



#include "fecbutton.moc"
