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

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QTabWidget>

#include "widgets/feecard.h"

#include "widgets/branch.h"
#include "widgets/rcu.h"

//#pragma GCC diagnostic ignored "-Weffc++"
#include <qdebug.h>
#include "widgets/module.h"
#include "widgets/moduleTabs.h"
#include "../pilogger/gui/logviewer.h"
#include "../pilogger/backend/pilogger.h"
#include <QVBoxLayout>
//#pragma GCC diagnostic pop

phosGui::phosGui ( QWidget* parent, Qt::WindowFlags flags )
: QMainWindow ( parent, flags ),
  _tabWidget(0),
  _logViewer(0)
{
    init();
}

phosGui::~phosGui()
{

}

void phosGui::init()
{
  //setFixedSize(1600, 900);
  setupWidgets();
  setupMenuBar();
  setupConnections();
}

void phosGui::setupWidgets()
{
  QVBoxLayout *mainLayout = new QVBoxLayout;
//  setupTabs();
//  setCentralWidget(_tabWidget);
 
  //Module_t module0(0);
  //module *mod0 = new module(module0, this);
  //mod0->setGeometry(10, menuBar()->y() + menuBar()->height());
  
  moduleTabs *tabs = new moduleTabs();
  setCentralWidget(tabs);

  _logViewer = new LogViewer();
  
  
//  QVBoxLayout *tabsLayout = new QVBoxLayout(tabsLayout);
  mainLayout->addWidget(tabs);
  mainLayout->addWidget(_logViewer);
  
//  mainLayout->setGeometry(QRect(10, 10, this->width(), this->height()));
  
//   setLayout(mainLayout);
  
  
  //Rcu_t rcu0(0, 0);
  //rcu *r0 = new rcu(rcu0, this);
  //r0->setGeometry(10, menuBar()->y() + menuBar()->height());
  
}

void phosGui::setupConnections()
{
  connect(phosDcsLogging::Instance(), SIGNAL(LoggingReceived()), this, SLOT(log()));
  phosDcsLogging::Instance()->Logging ( std::string ( "Connected..." ), LOG_LEVEL_INFO );
  connect ( PiLogger::getInstance(), SIGNAL ( newLog ( LogElement ) ), _logViewer, SLOT ( addElement ( LogElement ) ) );
  //PIERROR("Starting Logger...") //TODO; determin: was this line put here simply for testing, if so, should it be completely removed?
}

void phosGui::setupMenuBar()
{
    QAction* a = new QAction ( this );
    a->setText ( "Quit" );
    connect ( a, SIGNAL ( triggered() ), SLOT ( close() ) );
    menuBar()->addMenu ( "File" )->addAction ( a );

}

void phosGui::setupTabs()
{
  _tabWidget = new QTabWidget(this);
}

void phosGui::log()
{
  qDebug() << phosDcsLogging::Instance()->GetLogViewerString().data();
}


#include "phosgui.moc"
