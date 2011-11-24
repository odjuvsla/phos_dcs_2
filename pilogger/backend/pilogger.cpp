#include "pilogger.h"
#include <QDebug>
#include <QMutex>
#include <QFile>
#include <iostream>

PiLogger *PiLogger::instance = 0;

PiLogger::PiLogger(QObject *parent) : QObject(parent)
,mutex_lock(0)
,log_file(0)
,enabled_log_levels(
		    LogState::FATAL.id|LogState::CRITICAL.id|LogState::ERROR.id|
		    LogState::WARNING.id|LogState::SUCCESS.id|LogState::NORMAL.id|
		    LogState::INFORMATION.id|LogState::DEBUG.id
		   )
,enabled_log_levels_file(enabled_log_levels)
,enabled_log_levels_console(enabled_log_levels)
,enabled_log_levels_emit(enabled_log_levels)
{
  mutex_lock = new QMutex(QMutex::Recursive);
  
  createLogFile();
}

PiLogger::~PiLogger()
{
}

PiLogger* PiLogger::getInstance()
{
  if(!instance)
  {
    instance = new PiLogger;
  }
  if(!instance)
  {
    QTextStream(stderr) << "Cannot create instance of logger! Exiting...\n";
    exit(-1);

  }
  return instance;
}

void PiLogger::logging(LogElement log)
{
  this->mutex_lock->lock();
  if((enabled_log_levels_file & log.getState().id))
  {
    logToFile(log);
  }
  if((enabled_log_levels_console & log.getState().id))
  {
    logToConsole(log);
  }
  if((enabled_log_levels_emit & log.getState().id))
  {
    emit newLog(log);
  }
  
  
  this->mutex_lock->unlock();
}

void PiLogger::logging(QString text, const LogState& state, const QString file, const int lineNumber)
{
  this->mutex_lock->lock();
  logging(LogElement(0, QDateTime::currentDateTime(), text, state, file, lineNumber));
  this->mutex_lock->unlock();
}

void PiLogger::logToFile(LogElement& log)
{
  this->mutex_lock->lock();
  QTextStream out(this->log_file);
  out << log << endl;
  this->mutex_lock->unlock();
}

void PiLogger::logToConsole(LogElement& log)
{
  this->mutex_lock->lock();
  QTextStream out(stdout);
  out <<  log << endl;
  this->mutex_lock->unlock();
}


int PiLogger::createLogFile()
{
  this->mutex_lock->lock();
  log_file = new QFile("log.txt");
  if(!log_file->open(QIODevice::WriteOnly))
  {
    PICRIT("Could not create log file!");
    return -1;
  }
  this->mutex_lock->unlock();
  return 0;
}

quint16 PiLogger::setLogMinLevel(const LogState &state, quint16 &value)
{
  int level = state.id;
  value = 0;
  if(level != LogState::NONE.id)
  {
    value = 0x0;
    for(int i = level; i <= LogState::NSTATES ; i++)
    {
      value = value|(0x1<<(i-1));
    }
    
  }
  return value;
}

quint16 PiLogger::enableLogLevel(const LogState& state, quint16 &value)
{
  value |= state.id;
  return value;
}

quint16 PiLogger::disableLogLevel(const LogState& state, quint16 &value)
{
  value &= ~state.id;
  return value;
}

quint16 PiLogger::enableAllLogLevels()
{
  return setLogMinLevelGlobal(LogState::DEBUG);
}
quint16 PiLogger::disableAllLogLevels()
{
  return setLogMinLevelGlobal(LogState::NONE);
}
quint16 PiLogger::setLogMinLevelConsole(const LogState& state)
{
  this->mutex_lock->lock();
  int res = setLogMinLevel(state, enabled_log_levels_console);
  QString info;
  QTextStream s(&info);
  s << "Setting log level for console: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();
  return res;

}
quint16 PiLogger::setLogMinLevelEmit(const LogState& state)
{
  this->mutex_lock->lock();
  int res = setLogMinLevel(state, enabled_log_levels_emit);
  QString info;
  QTextStream s(&info);
  s << "Setting log level for emit: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();

  return res;

}
quint16 PiLogger::setLogMinLevelFile(const LogState& state)
{
  this->mutex_lock->lock();
  int res = setLogMinLevel(state, enabled_log_levels_file);
  QString info;
  QTextStream s(&info);
  s << "Setting log level for file: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();
  return res;
}
quint16 PiLogger::setLogMinLevelGlobal(const LogState& state)
{
  this->mutex_lock->lock();
  int level = setLogMinLevel(state, enabled_log_levels);
  enabled_log_levels_file = enabled_log_levels;
  enabled_log_levels_console = enabled_log_levels;
  enabled_log_levels_emit = enabled_log_levels;
  
  QString info;
  QTextStream s(&info);
  s << "Setting global minmum log level: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();
  return level;
  
}

quint16 PiLogger::enableLogLevelFile(const LogState& state)
{
  this->mutex_lock->lock();
  enabled_log_levels_file |= state.id;
  QString info;
  QTextStream s(&info);
  s << "Enabling log level for file: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();
  return enabled_log_levels_file;
}

quint16 PiLogger::disableLogLevelFile(const LogState& state)
{
  this->mutex_lock->lock();
  enabled_log_levels_file &= ~state.id;
  QString info;
  QTextStream s(&info);
  s << "Disabling log level for file: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();
  return enabled_log_levels_file;
}


quint16 PiLogger::enableLogLevelConsole(const LogState& state)
{
  this->mutex_lock->lock();
  enabled_log_levels_file |= state.id;
  QString info;
  QTextStream s(&info);
  s << "Enabling log level for console: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();
  return enabled_log_levels_console;
}

quint16 PiLogger::disableLogLevelConsole(const LogState& state)
{
  this->mutex_lock->lock();
  enabled_log_levels_console &= ~state.id;
  QString info;
  QTextStream s(&info);
  s << "Disabling log level for console: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();
  return enabled_log_levels_console;
}

quint16 PiLogger::enableLogLevelEmit(const LogState& state)
{
  this->mutex_lock->lock();
  enabled_log_levels_emit |= state.id;
  QString info;
  QTextStream s(&info);
  s << "Enabling log level for emit: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();
  return enabled_log_levels_emit;
}

quint16 PiLogger::disableLogLevelEmit(const LogState& state)
{
  this->mutex_lock->lock();
  enabled_log_levels_emit &= ~state.id;
  QString info;
  QTextStream s(&info);
  s << "Disabling log level for emit: " << state;
  PIINFO("%s",info.toStdString().c_str());
  this->mutex_lock->unlock();
  return enabled_log_levels_emit;
}


