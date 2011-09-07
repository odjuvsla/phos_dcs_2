#include "phosgui.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QTabWidget>

#include "widgets/feecard.h"
#include "widgets/branch.h"

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
  setFixedSize(1280, 720);
  setupWidgets();
  setupMenuBar();
  setupConnections();
}

void phosGui::setupWidgets()
{
  setupTabs();
  setCentralWidget(_tabWidget);
  Branch_t b(0,0,0);
  branch *b0 = new branch(b, this);
  b0->setGeometry(10, menuBar()->y() + menuBar()->height());
}

void phosGui::setupConnections()
{
    //l->setText( "Hello World!" );
    // setCentralWidget( l );

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


#include "phosgui.moc"
