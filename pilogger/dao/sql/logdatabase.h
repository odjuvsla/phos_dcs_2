#ifndef LOGDATABASE_H
#define LOGDATABASE_H

class LogDataBase
{

public:
    LogDataBase();

    ~LogDataBase();
    
    int initialize();
    
    
private:
  
  //! Prohibited
    LogDataBase(const LogDataBase& other);
    virtual LogDataBase& operator=(const LogDataBase& other);
    virtual bool operator==(const LogDataBase& other) const;
};

#endif // LOGDATABASE_H
