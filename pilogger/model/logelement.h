#ifndef LOGELEMENT_H
#define LOGELEMENT_H

// Lib includes
#include <QString>
#include <QDateTime>
#include <QDataStream>
#include <qvector.h>
#include <QTextStream>

class LogState //! Class cannot be constructed, only static instances of State may be used
  
{
public:

  //! Copy constructor 
  LogState(const LogState &s) : id(s.id), name(s.name) {}
  
  //! Identifier of the state
  int id;
  QString name;

  //! Assignment
  LogState & operator=(const LogState &s) { if(this == &s) return *this; this->id = s.id; this->name = s.name; return *this;}
  
  //! Comparison (should only be necessary to check the ID
  bool operator==(const LogState &obj)const {return id == obj.id;}
  
  //! Stream operators
  friend QDataStream &operator>>(QDataStream &in, LogState &obj){ in >> obj.id; in >> obj.name; return in;}
  
  friend QDataStream &operator<<(QDataStream &out, const LogState &obj){ out << obj.id; out << obj.name; return out;}

    //! Stream operators
  friend QTextStream &operator<<(QTextStream &out, const LogState &obj);

  // Define our states here, give them IDs from bitshifts -> easier to mask later
  static const LogState NONE;//(0, "NONE");
  static const LogState DEBUG;//(1, "DEBUG");
  static const LogState INFORMATION;//(1<<1, "INFO");
  static const LogState NORMAL;//(1<<2, "NORMAL");
  static const LogState SUCCESS;//(1<<3, "SUCCESS");
  static const LogState WARNING;//(1<<4, "WARNING");
  static const LogState ERROR;//(1<<5, "CRITICAL");
  static const LogState CRITICAL;//(1<<6, "CRITICAL");
  static const LogState FATAL;//(1<<7, "FATAL");
  
  static const int NSTATES;
  
private:
  
  //! Prohibited
  LogState();
  LogState(int i, QString n) : id(i), name(n) {;}

  
};

class LogElement
{
public:

    // Constructors
    LogElement();
    LogElement(const LogElement &obj);
    LogElement(int id, QDateTime dateTime, QString text, const LogState state, const QString filename = QString(""), const int lineNumber = 0);
    ~LogElement();

    // Set methods
    void setId(const int &id);
    void setDateTime(const QDateTime &dateTime);
    void setText(const QString &text);
    void setState(const LogState state);
    void setFilename(const QString &name);
    void setLineNumber(const int lineNumber);
    
    

    // Get methods
    int getId() const;
    QDateTime getDateTime() const;
    QString getText() const;
    const LogState getState() const;
    QString getFilename() const;
    int getLineNumber() const;

    // = operator
    LogElement& operator=(const LogElement&);

    // Stream operators
    friend QDataStream &operator>>(QDataStream &in, LogElement &obj);
    friend QDataStream &operator<<(QDataStream &out, const LogElement &obj);
    
    friend QTextStream &operator<<(QTextStream &out, const LogElement &obj);

private:

    int id;
    QDateTime dateTime;
    QString text;
    LogState state;
    QString filename;
    int lineNumber;
    
};

#endif // LOGELEMENT_H
