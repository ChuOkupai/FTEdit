#pragma once
#ifndef EVENT_HH
# define EVENT_HH
# include <QString>
# include "Properties.hh"
# include "Distribution.hh"

class Event
{
private:
    Properties prop;
    Distribution* distrib = nullptr;

public:
    Event(QString name);

    ~Event();
    
    Properties& getProperties();

    void setDistribution(Distribution* distrib);
    
    Distribution* getDistribution();
};

#endif
