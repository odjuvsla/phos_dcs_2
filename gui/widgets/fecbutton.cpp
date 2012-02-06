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

#include "phosconstants.h"
using namespace PHOS;

FecButton::FecButton (FecID fecID, QWidget* parent)
: QPushButton ( parent ),
  fecID(fecID),
  status(FEC_UNKNOWN)
{
  SetStatus(FEC_UNKNOWN, "Init value");
  
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

void FecButton::SetStatus(FecStatus newStatus, const QString& message)
{
  QString statusTip = QTime::currentTime().toString();
  

  if(status == FEC_ON) {
    setEnabled(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Button, Qt::green);
    setPalette(palette);
    statusTip.append(" - Status: On, ");
  } 
  else if( status == FEC_OFF) {
    setEnabled(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Button, Qt::red);
    setPalette(palette);
    statusTip.append(" - Status: Off, ");
  }
  //else if( status == FEC_ ) {
  //  setEnabled(false);
  //  statusTip.append(" - Status: Waiting, ");
  //}
  else if ( status == FEC_UNKNOWN ) {
    setEnabled(false);
    QColor defalutColor = QPalette().color(QPalette::Button);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Button, defalutColor);
    setPalette(palette);
    statusTip.append(" - Status: Unknown, ");
  }
  else
    phosDcsLogging::Instance()->Logging("FecButton::SetStatus, state not handled", LOG_LEVEL_ERROR);

  setStatusTip(statusTip.append(message));
}



#include "fecbutton.moc"
