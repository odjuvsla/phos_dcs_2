#include "logelement.h"
#include <QDateTime>

const LogState LogState::NONE(0, 		"NONE    ");
const LogState LogState::DEBUG(1, 		"DEBUG   ");
const LogState LogState::INFORMATION(1<<2, 	"INFO    ");
const LogState LogState::NORMAL(1<<3, 		"NORMAL  ");
const LogState LogState::SUCCESS(1<<4, 		"SUCCESS ");
const LogState LogState::WARNING(1<<5, 		"WARNING ");
const LogState LogState::ERROR(1<<6, 		"ERROR   ");
const LogState LogState::CRITICAL(1<<7, 	"CRITICAL");
const LogState LogState::FATAL(1<<8, 		"FATAL   ");

const int LogState::NSTATES = 9; //Including NONE

// Constructors
LogElement::LogElement() : id(0), state(LogState::NONE), filename(""), lineNumber(0)
{}

LogElement::LogElement(int id, QDateTime dateTime, QString text, const LogState state, const QString filename, const int line):
      id(id), dateTime(dateTime), text(text), state(state), filename(filename), lineNumber(line){}

LogElement::LogElement(const LogElement &obj): id(obj.id), dateTime(obj.dateTime), text(obj.text), state(obj.state), filename(obj.filename), lineNumber(obj.lineNumber){}

LogElement::~LogElement(){}

// Set methods
void LogElement::setId(const int &id){ this->id = id; }
void LogElement::setDateTime(const QDateTime &dateTime){ this->dateTime = dateTime; }
void LogElement::setText(const QString &text){ this->text = text; }
void LogElement::setState(const LogState state){ this->state = state; }
void LogElement::setFilename(const QString& name){this->filename = name; }
void LogElement::setLineNumber(const int lineNumber){this->lineNumber = lineNumber;}

// Get methods
int LogElement::getId() const{ return this->id; }
QDateTime LogElement::getDateTime() const{ return this->dateTime; }
QString LogElement::getText() const{ return this->text; }
const LogState LogElement::getState() const{ return this->state; }

// = operator
LogElement& LogElement::operator=(const LogElement &obj){
    if(this != &obj){
        id = obj.id;
        dateTime = obj.dateTime;
        text = obj.text;
        state = obj.state;
	filename = obj.filename;
	lineNumber = obj.lineNumber;
    }
    return *this;
}

// Stream in operator
QDataStream &operator>>(QDataStream &in, LogElement &obj){
        in >> obj.id;
        in >> obj.dateTime;
        in >> obj.text;
        in >> obj.state;
	in >> obj.filename;
	in >> obj.lineNumber;
        return in;
}

// Stream out operator
QDataStream &operator<<(QDataStream &out, const LogElement &obj){
        out << obj.id;
        out << obj.dateTime;
        out << obj.text;
        out << obj.state;
	out << obj.filename;
	out << obj.lineNumber;
        return out;
}

QTextStream& operator<<(QTextStream& out, const LogElement& obj)
{
	out << obj.state;
	out << " : ";
	QString format("yyyy-MM-dd : hh:mm:ss");
	out << obj.dateTime.toString(format);
	out << " : Message: ";
        out << obj.text;
	if(obj.filename != "") 
	{
	  out << right << " \t\t-> " << obj.filename;
	  if(obj.lineNumber)
	  {
	    out << ":" << obj.lineNumber << left;
	  }
	}
        return out;

}

QTextStream &operator<<(QTextStream &out, const LogState &obj)
{ 
  out << obj.name;
  return out;
  
}



