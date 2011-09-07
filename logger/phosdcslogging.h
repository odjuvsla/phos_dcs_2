#ifndef PHOSDCSLOGGING_H
#define PHOSDCSLOGGING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <QObject>

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
      fFileLogLevel = level;
    }

    /** Set the logging level for the terminal */
    void SetTerminalOutputLevel ( unsigned int level )
    {
      fTerminalLogLevel = level;
    }

    /** Set the logging level for the log viewer */
    void SetLogViewerLevel ( unsigned int level )
    {
      fLogViewerLevel = level;
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
    static phosDcsLogging* fInstance;

    /** The log level for the log file */
    unsigned int fFileLogLevel;

    /** The log level for the terminal */
    unsigned int fTerminalLogLevel;

    /** The log level for the log viewer */
    unsigned int fLogViewerLevel;

    /** The stream to the log file */
    std::ofstream fLogFile;

    /** The log viewer stream */
    std::stringstream fLogViewerStringStream;

    /** Vector containing strings corresponding to the different log levels */
    std::vector<std::string> fLogLevels;
    
    /** Mutex */
    QMutex *fMutexLock;

    /** Copy constructor - not implemented */
    phosDcsLogging ( const phosDcsLogging & );

    /** Assignment operator - not implemented */
    phosDcsLogging & operator = ( const phosDcsLogging );
    
  signals:
    
    void LoggingReceived(void);

  };


#endif
