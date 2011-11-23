#include "../pilogger.h"
#include <QtCore/QCoreApplication>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    PiLogger *logger = PiLogger::getInstance();
    QString logString;
    QTextStream s(&logString);

    logger->setLogMinLevelGlobal(LogState::INFORMATION);

    PIDEBUG("This is debug, you shouldn't see this.");
    
    logger->enableAllLogLevels();
    logger->disableAllLogLevels();
    logger->enableLogLevelFile(LogState::DEBUG);
    
    PIFATAL("This is fatal, you shouldn't see this.")
    
    logger->enableAllLogLevels();
    
    PIDEBUG("PIDEBUG on %d", LOGDEBUG);
    PIINFO("PIINFO on %d", LOGINFO);
    PINORMAL("PINORMAL on %d", LOGNORMAL);
    PISUCCESS("PISUCCESS on %d", LOGSUCCESS);
    PIWARNING("PIWARNING on %d", LOGWARNING);
    PIERROR("PIERROR on %d", LOGERROR);
    PICRIT("PICRIT on %d", LOGCRITICAL);
    PIFATAL("PIFATAL on %d", LOGFATAL);
    
    // This is also possible:
    s << "We should use string literals like this: ";
    PIDEBUG("%s", logString.toStdString().c_str());
    return a.exec();
}