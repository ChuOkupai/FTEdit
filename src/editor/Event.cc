#include "Event.hh"

Event::Event(QString name) : prop(name){}

Event::~Event() {}

void Event::setDistribution(Distribution *distribution)
{
	if (this->distribution)
		this->distribution->getProperties().decrementRefCount();
	this->distribution = distribution;
	this->distribution->getProperties().incrementRefCount();
}

Distribution* Event::getDistribution()
{
	return (distribution);
}

Properties& Event::getProperties()
{
	return (prop);
}

