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

#ifndef MODULETABS_H
#define MODULETABS_H

//#pragma GCC diagnostic ignored "-Weffc++"
#include <QtGui/qwidget.h>
#include <qtabwidget.h>




class ModuleTabs : public QTabWidget
{
  Q_OBJECT
public:
  
  explicit ModuleTabs(QWidget *parent = 0);
  virtual ~ModuleTabs();
  
private:
  
  
  /** Prohibited */
    //moduleTabs();
    ModuleTabs(const ModuleTabs& other);
    ModuleTabs& operator=(const ModuleTabs& other);
    bool operator==(const ModuleTabs& other) const;
};
//#pragma GCC diagnostic error "-Weffc++"
#endif // MODULETABS_H
