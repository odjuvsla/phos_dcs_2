#include "phosdcslogging.h"
#include "qmutex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include "phosutils.h"

using namespace std;

phosDcsLogging* phosDcsLogging::fInstance = 0;

phosDcsLogging::phosDcsLogging() : QObject(),
        fFileLogLevel ( LOG_LEVEL_EXTREME_VERBOSE ),
        fTerminalLogLevel ( LOG_LEVEL_VERBOSE ),
        fLogViewerLevel ( LOG_LEVEL_DEFAULT ),
        fLogFile(),
        fLogViewerStringStream(),
        fMutexLock ( 0 )
{

    fMutexLock = new QMutex;

    fLogLevels.push_back ( string ( "NONE" ) );
    fLogLevels.push_back ( string ( "ERROR" ) );
    fLogLevels.push_back ( string ( "WARNING" ) );
    fLogLevels.push_back ( string ( "INFO" ) );
    fLogLevels.push_back ( string ( "VERBOSE" ) );
    fLogLevels.push_back ( string ( "VERY_VERBOSE" ) );
    fLogLevels.push_back ( string ( "EXTREME_VERBOSE" ) );

    stringstream filename;
    stringstream timestamp;
    stringstream datestamp;


//TODO: Make safer solution to this!
    mkdir ( "log/", 0777 );

    GetTimeStamp ( timestamp, datestamp );
    filename << "log/" << datestamp.str() << "_" << timestamp.str() << ".log";

    fLogFile.open ( filename.str().c_str() );
    //fLogFile.open("log/test.log");

    if ( fLogFile.is_open() == false )
    {
        cerr << "Could not open log file!" << endl;
        cerr << "Check permissions and if log/ directory exists in current directory (should be automatic)" << endl;
        cerr << "Exiting..." << endl;
        exit ( 1 );
    }

    Logging ( string ( "Starting Logger..." ), LOG_LEVEL_INFO );

}


phosDcsLogging::~phosDcsLogging()
{
    fLogFile.close();
}

phosDcsLogging* phosDcsLogging::Instance()
{
    if ( !fInstance )
    {
        fInstance = new phosDcsLogging();
    }
    return fInstance;
}

void phosDcsLogging::Logging ( string logmsg, unsigned int level, std::string filename, int line )
{
    fMutexLock->lock();
    string tmplogmsg = fLogLevels[level] + ": " += logmsg;
    if ( level <= fFileLogLevel )
    {
        string outmsg = tmplogmsg;
        AddFileAndLine ( filename, line, outmsg );
        LogFile ( outmsg );
    }
    if ( level <= fTerminalLogLevel )
    {
        string outmsg = tmplogmsg;
        AddFileAndLine ( filename, line, outmsg );
        LogTerminal ( outmsg );
    }
    if ( level <= fLogViewerLevel )
    {
        LogViewer ( tmplogmsg );
    }
    fMutexLock->unlock();
}

void phosDcsLogging::LogFile ( string logmsg )
{
    stringstream timestamp;
    stringstream datestamp;
    GetTimeStamp ( timestamp, datestamp );
    fLogFile << timestamp.str() << ": " << logmsg << endl;
}

void phosDcsLogging::LogTerminal ( string logmsg )
{
    cout << logmsg << endl;
}

void phosDcsLogging::LogViewer ( string logmsg )
{
    stringstream timestamp;
    stringstream datestamp;
    GetTimeStamp ( timestamp, datestamp );
    fLogViewerStringStream << timestamp.str() << ": " << logmsg << endl;
}

string phosDcsLogging::GetLogViewerString()
{
    string tmpstring = fLogViewerStringStream.str();
    fLogViewerStringStream.str ( " " );
    return tmpstring;
}

void phosDcsLogging::GetTimeStamp ( stringstream& timestamp, stringstream& datestamp )
{
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    if ( timestamp )
    {
        timestamp.fill ( '0' );
        timestamp.width ( 2 );
        timestamp << timeinfo->tm_hour << ":";
        timestamp.width ( 2 );
        timestamp << timeinfo->tm_min << ":";
        timestamp.width ( 2 );
        timestamp << timeinfo->tm_sec;
    }
    if ( datestamp )
    {-
        datestamp.fill ( '0' );
        datestamp << timeinfo->tm_year + 1900 << ".";
        datestamp.width ( 2 );
        datestamp << timeinfo->tm_mon + 1 << ".";
        datestamp.width ( 2 );
        datestamp << timeinfo->tm_mday;
    }
}

void phosDcsLogging::AddFileAndLine ( string filename, int line, string& logmsg )
{
    if ( line >= 0 )
    {
        int found= filename.find_last_of ( "/" );
        logmsg += " \t\t\t=> " + filename.substr ( found + 1 ) + ":" + to_string ( line ) ;
    }

}

#include "phosdcslogging.moc"











