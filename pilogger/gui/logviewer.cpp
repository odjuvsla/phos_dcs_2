#include "logviewer.h"

LogViewer::LogViewer(QWidget *parent) :
    QTableWidget(parent)
{
    initializeLog();
    loadDefaultColors();
}

LogViewer::~LogViewer()
{
}

void LogViewer::setupSignals(){

}

void LogViewer::initializeLog(){
    rowCount = 0;
    showState = 0;
    this->setColumnCount(4);
    this->setHorizontalHeaderItem(0, new QTableWidgetItem("Level"));
    this->setHorizontalHeaderItem(1, new QTableWidgetItem("Time"));
    this->setHorizontalHeaderItem(2, new QTableWidgetItem("Subject"));
    this->setHorizontalHeaderItem(3, new QTableWidgetItem("File"));
    this->setColumnWidth(2, 800);
    this->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    this->horizontalHeader()->setVisible(true);
    this->verticalHeader()->setVisible(false);
    this->setShowGrid(true);
    this->verticalHeader()->setDefaultSectionSize(20);
    this->setGridStyle(Qt::SolidLine);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->horizontalHeader()->setStretchLastSection(true);
    this->horizontalHeader()->setResizeMode(0,QHeaderView::Interactive);
    this->horizontalHeader()->resizeSection(0, 70);
    this->setIconSize(QSize(16, 16));
    //this->setStyleSheet("#TableElements {background: transparent;}");
    this->setRowCount(20);
}

void LogViewer::loadDefaultColors(){
    colors[LogState::SUCCESS.id] = Qt::darkGreen;
    colors[LogState::INFORMATION.id] = Qt::blue;
    colors[LogState::NORMAL.id] = Qt::black;
    colors[LogState::WARNING.id] = Qt::magenta;
    colors[LogState::CRITICAL.id] = Qt::red;
}

bool LogViewer::addElement(const LogElement &element){
    this->insertRow(rowCount);

    QTableWidgetItem* dateTimeItem = new QTableWidgetItem(element.getDateTime().toString("hh:mm:ss"));

    QTableWidgetItem* textItem = new QTableWidgetItem(element.getText());
    
    QTableWidgetItem* levelItem = new QTableWidgetItem(element.getState().name);

    QString lineNo;
    lineNo.sprintf("%d", element.getLineNumber());
    QTableWidgetItem* fileItem = new QTableWidgetItem(element.getFilename()+":" + lineNo) ;

    /*dateTimeItem->setFont(QFont("Arial", 10));
    textItem->setFont(QFont("Arial", 10));*/
    if(element.getState() == LogState::WARNING) 
    {
       textItem->setIcon(this->style()->standardIcon(QStyle::SP_MessageBoxWarning));
       
    }
    if(element.getState() == LogState::ERROR) 
    {
      levelItem->setBackgroundColor(Qt::yellow);
      textItem->setIcon(this->style()->standardIcon(QStyle::SP_MessageBoxWarning));
    }
    if(element.getState() == LogState::FATAL) 
    {
      levelItem->setBackgroundColor(Qt::red);
      textItem->setIcon(this->style()->standardIcon(QStyle::SP_MessageBoxCritical));
    }
    
    textItem->setTextColor(colors[element.getState().id]);

    this->setItem(rowCount, 0, levelItem);
    this->setItem(rowCount, 1, dateTimeItem);
    this->setItem(rowCount, 2, textItem);
    this->setItem(rowCount, 3, fileItem);
    
    allElements.append(element);
    rowCount++;
    return true;
}

bool LogViewer::addElement(const QString& text, const LogState& state, QDateTime dateTime){

    LogElement element;
    element.setId(rowCount+1);
    element.setText(text);
    element.setState(state);
    element.setDateTime(dateTime);

    return addElement(element);
}

void LogViewer::clearLog(){

}

QSize LogViewer::sizeHint() const
{
  
  return QSize(1000, 750);
}



