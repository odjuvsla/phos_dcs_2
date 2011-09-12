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

#pragma GCC diagnostic ignored "-Weffc++"
#include <qdebug.h>
#include "widgets/module.h"
#include "widgets/moduleTabs.h"
#include <QVBoxLayout>
#pragma GCC diagnostic pop

phosGui::phosGui ( QWidget* parent, Qt::WindowFlags flags ) : QMainWindow ( parent, flags )
,_tabWidget(0)
{
    init();
}

phosGui::~phosGui()
{

}

void phosGui::init()
{
  setFixedSize(1600, 900);
  setupWidgets();
  setupMenuBar();
  setupConnections();
}

void phosGui::setupWidgets()
{
//  setupTabs();
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
//  setCentralWidget(_tabWidget);
 
  //Module_t module0(0);
  //module *mod0 = new module(module0, this);
  //mod0->setGeometry(10, menuBar()->y() + menuBar()->height());
  
  moduleTabs *tabs = new moduleTabs(this);
  setCentralWidget(tabs);
  QVBoxLayout *tabsLayout = new QVBoxLayout(mainLayout);
  tabsLayout->addWidget(tabs);
  tabsLayout->setGeometry(QRect(10, 10, this->width(), this->height()));
  
  //Rcu_t rcu0(0, 0);
  //rcu *r0 = new rcu(rcu0, this);
  //r0->setGeometry(10, menuBar()->y() + menuBar()->height());
  
}

void phosGui::setupConnections()
{
  connect(phosDcsLogging::Instance(), SIGNAL(LoggingReceived()), this, SLOT(log()));
  phosDcsLogging::Instance()->Logging ( std::string ( "Connected..." ), LOG_LEVEL_INFO );

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
