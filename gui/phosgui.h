#ifndef PHOSGUI_H
#define PHOSGUI_H

#include <QtGui/QMainWindow>

class QTabWidget;

class phosGui : public QMainWindow
{
Q_OBJECT
public:
  
  /** Constructor */
  explicit phosGui ( QWidget* parent = 0, Qt::WindowFlags flags = 0 );
  
  /** Destructor */
  virtual ~phosGui();
    
private:
    
  /** Initialize the gui */
  void init();
  
  /** Setup the widgets */
  void setupWidgets();
  
  /** Setup signals and slots */
  void setupConnections();
  
  /** Setup the menu bar */
  void setupMenuBar();

  /** Setup the tabs */
  void setupTabs();
  
  /** Tab widget */
  QTabWidget *_tabWidget;
  
};

#endif // PHOSGUI_H
