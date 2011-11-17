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

#include "phosdcslogging.h"
//#pragma GCC diagnostic ignored "-Weffc++"
#include "qmutex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "phosutils.h"

using namespace std;

phosDcsLogging* phosDcsLogging::_instance = 0;

phosDcsLogging::phosDcsLogging() : QObject()
        ,_fileLogLevel ( LOG_LEVEL_EXTREME_VERBOSE )
        ,_terminalLogLevel ( LOG_LEVEL_VERBOSE )
        ,_logViewerLevel ( LOG_LEVEL_DEFAULT )
        ,_logFile()
        ,_logViewerStringStream()
        ,_logLevels(0)
        ,_mutexLock ( 0 )
{

    _mutexLock = new QMutex;

    _logLevels.push_back ( string ( "NONE" ) );
    _logLevels.push_back ( string ( "ERROR" ) );
    _logLevels.push_back ( string ( "WARNING" ) );
    _logLevels.push_back ( string ( "INFO" ) );
    _logLevels.push_back ( string ( "VERBOSE" ) );
    _logLevels.push_back ( string ( "VERY_VERBOSE" ) );
    _logLevels.push_back ( string ( "EXTREME_VERBOSE" ) );

    stringstream filename;
    stringstream timestamp;
    stringstream datestamp;

    if (mkdir ( "log/", 0777 ) < 0)
    {
        if (errno != EEXIST)
        {
            perror("Creating directory \"log/\"");
            exit(-1);
        }
    }

    GetTimeStamp ( timestamp, datestamp );
    filename << "log/" << datestamp.str() << "_" << timestamp.str() << ".log";

    _logFile.open ( filename.str().c_str() );
    //fLogFile.open("log/test.log");

    if ( _logFile.is_open() == false )
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
    _logFile.close();
}

phosDcsLogging* phosDcsLogging::Instance()
{
    if ( !_instance )
    {
        _instance = new phosDcsLogging();
    }
    return _instance;
}

void phosDcsLogging::Logging ( string logmsg, unsigned int level, std::string filename, int line )
{
  
    QMutexLocker locker(_mutexLock);
    string tmplogmsg = _logLevels[level] + ": " += logmsg;
    if ( level <= _fileLogLevel )
    {
        string outmsg = tmplogmsg;
        AddFileAndLine ( filename, line, outmsg );
        LogFile ( outmsg );
    }
    if ( level <= _terminalLogLevel )
    {
        string outmsg = tmplogmsg;
        AddFileAndLine ( filename, line, outmsg );
        LogTerminal ( outmsg );
    }
    if ( level <= _logViewerLevel )
    {
        LogViewer ( tmplogmsg );
    }
    emit(LoggingReceived());
}

void phosDcsLogging::LogFile ( string logmsg )
{
    stringstream timestamp;
    stringstream datestamp;
    GetTimeStamp ( timestamp, datestamp );
    _logFile << timestamp.str() << ": " << logmsg << endl;
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
    _logViewerStringStream << timestamp.str() << ": " << logmsg << endl;
}

string phosDcsLogging::GetLogViewerString()
{
    string tmpstring = _logViewerStringStream.str();
    _logViewerStringStream.str ( " " );
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
    {
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











