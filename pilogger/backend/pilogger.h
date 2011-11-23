#ifndef PILOGGER_H
#define PILOGGER_H

#include <QObject>
#include <QString>
#include <cstdio>
#include <cstdarg>
#include "../model/logelement.h"

#define LOGDEBUG	1
#define LOGINFO		1
#define LOGNORMAL	1
#define LOGSUCCESS	1
#define LOGWARNING	1
#define LOGERROR	1
#define LOGCRITICAL	1
#define LOGFATAL	1

// Please do not call this, but use the macros for the specific log levels
#define PIDOLOG(state, text, args...) { 									\
					QString s; 								\
					s.sprintf(text, ## args);						\
					PiLogger::getInstance()->logging(s, state, __FILE__, __LINE__);		\
				      }
				      
#define PIDEBUG(text, args...) {										\
				  if(LOGDEBUG) {								\
				    PIDOLOG(LogState::DEBUG, text, ## args);					\
				  }										\
				}

#define PIINFO(text, args...) {											\
				  if(LOGINFO) {									\
				    PIDOLOG(LogState::INFORMATION, text, ## args);				\
				  }										\
				}

#define PINORMAL(text, args...) {										\
				  if(LOGNORMAL) {								\
				    PIDOLOG(LogState::NORMAL, text, ## args);					\
				  }										\
				}

#define PISUCCESS(text, args...) {										\
				  if(LOGSUCCESS) {								\
				    PIDOLOG(LogState::SUCCESS, text, ## args);					\
				  }										\
				}

#define PIWARNING(text, args...) {										\
				  if(LOGWARNING) {								\
				    PIDOLOG(LogState::WARNING, text, ## args);					\
				  }										\
				}

#define PIERROR(text, args...) {										\
				  if(LOGERROR) {								\
				    PIDOLOG(LogState::ERROR, text, ## args);					\
				  }										\
				}

#define PICRIT(text, args...) {											\
				  if(LOGCRITICAL) {								\
				    PIDOLOG(LogState::CRITICAL, text, ## args);					\
				  }										\
				}

#define PIFATAL(text, args...) {										\
				  if(LOGFATAL) {								\
				    PIDOLOG(LogState::FATAL, text, ## args);					\
				  }										\
				}


class QFile;

class QMutex;
class PiLogger : public QObject
{

    Q_OBJECT
public:

    virtual ~PiLogger();

    //! Get the instance
    static PiLogger* getInstance();

    //! Log a log element
    void logging ( LogElement log );

    //! Log a log element
    void logging ( QString text, const LogState &state, const QString fileName = QString ( "" ), const int lineNumber = 0 );

    //! Write log to file
    void logToFile ( LogElement &log );
    
    //! Write log to console
    void logToConsole( LogElement &log );

    //! Set the global minimum log level
    quint16 setLogMinLevelGlobal ( const LogState &state );

    //! Set the minimum log level for writing to file
    quint16 setLogMinLevelFile ( const LogState &state );

    //! Set the minimum log level for writing to console
    quint16 setLogMinLevelConsole ( const LogState &state );

    //! Set the minimum log level for writing to console
    quint16 setLogMinLevelEmit ( const LogState &state );

    //! Enable a specific log level
    quint16 enableLogLevelFile ( const LogState &state );

    //! Disable a specific log level
    quint16 disableLogLevelFile ( const LogState &state );

    //! Enable a specific log level
    quint16 enableLogLevelConsole ( const LogState &state );

    //! Disable a specific log level
    quint16 disableLogLevelConsole ( const LogState &state );

    //! Enable a specific log level
    quint16 enableLogLevelEmit ( const LogState &state );

    //! Disable a specific log level
    quint16 disableLogLevelEmit ( const LogState &state );

    //! Enable all log levels
    quint16 enableAllLogLevels();

    //! Enable all log levels
    quint16 disableAllLogLevels();

private:
    //! Set the minimum log level
    //! v is the value to write the log level
    quint16 setLogMinLevel ( const LogState &state, quint16 &v );

    //! Enable a specific log level
    quint16 enableLogLevel ( const LogState& state, quint16& value );

    //! Disable a specific log level
    quint16 disableLogLevel ( const LogState& state, quint16& value );

    //! Pointer to the logging instance
    static PiLogger* instance;

    explicit PiLogger ( QObject *parent = 0 );

    //! Create a log file
    int createLogFile();

    QMutex *mutex_lock;

    QFile *log_file;

    //! Globally enabled log levels
    quint16 enabled_log_levels;

    //! Enabled log levels for file
    quint16 enabled_log_levels_file;

    //! Enabled log levels for console
    quint16 enabled_log_levels_console;

    //! Enabled log levels for emit
    quint16 enabled_log_levels_emit;

    //! Inhibited
    PiLogger ( const PiLogger& other );
    PiLogger& operator= ( const PiLogger& other );
    bool operator== ( const PiLogger& other ) const;


signals:

    void newLog ( LogElement element );

};

#endif // PILOGGER_H
