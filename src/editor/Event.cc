#include "Event.hh"

Event::Event(QString name) : Properties(name){}

Event::~Event() {}

void Event::setDistribution(Distribution* distrib);
{
    if (!this->distrib)
        this->distrib = distrib;
}

Distribution* Event::getDistribution()
{
    return distrib;
}

Properties& Event::getProperties()
{
    return &prop;
}

