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

#ifndef PHOSGUI_H
#define PHOSGUI_H

#include <QtGui/QMainWindow>
#include "widgets/moduletabs.h"

class QTabWidget;
class LogViewer;

class PhosGui : public QMainWindow
{
Q_OBJECT
public:
  
  /** Constructor */
  explicit PhosGui ( QWidget* parent = 0, Qt::WindowFlags flags = 0 );
  
  /** Destructor */
  virtual ~PhosGui();
    
  
public slots:
  
  void log();

  
private:
    
  /** Initialize the gui */
  void init();
  
  /** Setup the widgets */
  void setupWidgets();
  
  /** Setup signals and slots */
  void setupConnections();
  
  /** Setup the menu bar */
  void setupMenuBar();

  /** Tab widget */
  ModuleTabs *tabs;
  QDockWidget *logDock;

  LogViewer *logViewer;

  QMenu *fileMenu;
  QMenu *viewMenu;
  QAction *quitAct;
  

  /* not permited */
  PhosGui(const PhosGui& );
  PhosGui operator=(const PhosGui&);
  
};

#endif // PHOSGUI_H
