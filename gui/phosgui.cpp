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

#include "phosgui.h"

#include <QtGui>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QTabWidget>

#include "widgets/fecbutton.h"

#include "widgets/branchwidget.h"
#include "widgets/rcuwidget.h"

//#pragma GCC diagnostic ignored "-Weffc++"
#include <qdebug.h>
#include "widgets/modulewidget.h"
#include "widgets/moduletabs.h"
#include "../pilogger/gui/logviewer.h"
#include "../pilogger/backend/pilogger.h"
#include <QVBoxLayout>
//#pragma GCC diagnostic pop

PhosGui::PhosGui ( QWidget* parent, Qt::WindowFlags flags )
: QMainWindow ( parent, flags ),
  tabs(0),
  logViewer(0)
{
    init();
}

PhosGui::~PhosGui()
{

}

void PhosGui::init()
{
  setupWidgets();
  setupMenuBar();
  setupConnections();

}

void PhosGui::setupWidgets()
{
  tabs = new ModuleTabs();
  logViewer = new LogViewer();
  logViewer->setMinimumHeight(120);

  
  logDock = new QDockWidget("LogViewer", this);
  logDock->setAllowedAreas(Qt::BottomDockWidgetArea);
  addDockWidget(Qt::BottomDockWidgetArea, logDock);

  setCentralWidget(tabs);
  logDock->setWidget(logViewer);
}

void PhosGui::setupConnections()
{
  connect(phosDcsLogging::Instance(), SIGNAL(LoggingReceived()), this, SLOT(log()));
  phosDcsLogging::Instance()->Logging ( std::string ( "Connected..." ), LOG_LEVEL_INFO );
  connect ( PiLogger::getInstance(), SIGNAL ( newLog ( LogElement ) ), logViewer, SLOT ( addElement ( LogElement ) ) );
  //PIERROR("Starting Logger...") //TODO; determin: was this line put here simply for testing, if so, should it be completely removed?
}

void PhosGui::setupMenuBar()
{
  quitAct = new QAction ( this );
  quitAct->setText ( "Quit" );
  connect ( quitAct, SIGNAL ( triggered() ), SLOT ( close() ) );
    

  fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction ( quitAct );

  viewMenu = menuBar()->addMenu("&View");
  viewMenu->addAction(logDock->toggleViewAction());
}

void PhosGui::log()
{
  qDebug() << phosDcsLogging::Instance()->GetLogViewerString().data();
}



#include "phosgui.moc"
