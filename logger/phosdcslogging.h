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

#ifndef PHOSDCSLOGGING_H
#define PHOSDCSLOGGING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#pragma GCC diagnostic ignored "-Weffc++"
#include <QObject>
//#pragma GCC diagnostic error "-Weffc++"

class QMutex;

const unsigned int LOG_LEVEL_NONE = 0;
const unsigned int LOG_LEVEL_ERROR = 1;
const unsigned int LOG_LEVEL_WARNING = 2;
const unsigned int LOG_LEVEL_INFO = 3;
const unsigned int LOG_LEVEL_VERBOSE = 4;
const unsigned int LOG_LEVEL_VERY_VERBOSE = 5;
const unsigned int LOG_LEVEL_EXTREME_VERBOSE = 6;

const unsigned int LOG_LEVEL_DEFAULT = LOG_LEVEL_INFO;

/**
 * Class used for logging for the PHOS APD GUI
 */
class phosDcsLogging : public QObject
  {
    Q_OBJECT
  public:

    /** Returns pointer to the logging instance. Creates the object if it don't exists */
    static phosDcsLogging* Instance();

    /** The function used for logging */
    void Logging ( std::string logmsg, unsigned int level, std::string filename = "", int line = -1);

    /** Set the logging level for the file output */
    void SetFileLoggingLevel ( unsigned int level )
    {
      _fileLogLevel = level;
    }

    /** Set the logging level for the terminal */
    void SetTerminalOutputLevel ( unsigned int level )
    {
      _terminalLogLevel = level;
    }

    /** Set the logging level for the log viewer */
    void SetLogViewerLevel ( unsigned int level )
    {
      _logViewerLevel = level;
    }

    /** Get the log viewer string */
    std::string GetLogViewerString();

    /** Get the current time/date stamp */
    void GetTimeStamp ( std::stringstream& timestamp, std::stringstream& datestamp );

  private:

    /** Default constructor (called by the Instance() function */
    phosDcsLogging();

    /** Default destructor */
    ~phosDcsLogging();

    /** Log message to file */
    void LogFile ( std::string logmsg );

    /** Log message to terminal */
    void LogTerminal ( std::string logmsg );

    /** Log message to log viewer */
    void LogViewer ( std::string logmsg );
    
    /** Add filename and line number to log message */
    void AddFileAndLine(std::string filename, int line, std::string &logmsg);

    /** Pointer to the logging instance */
    static phosDcsLogging* _instance;

    /** The log level for the log file */
    unsigned int _fileLogLevel;

    /** The log level for the terminal */
    unsigned int _terminalLogLevel;

    /** The log level for the log viewer */
    unsigned int _logViewerLevel;

    /** The stream to the log file */
    std::ofstream _logFile;

    /** The log viewer stream */
    std::stringstream _logViewerStringStream;

    /** Vector containing strings corresponding to the different log levels */
    std::vector<std::string> _logLevels;
    
    /** Mutex */
    QMutex *_mutexLock;

    /** Copy constructor - not implemented */
    phosDcsLogging ( const phosDcsLogging & );

    /** Assignment operator - not implemented */
    phosDcsLogging & operator = ( const phosDcsLogging );
    
  signals:
    
    void LoggingReceived(void);

  };


#endif
