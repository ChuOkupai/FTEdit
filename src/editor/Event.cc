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
bool Event::operator==(const Event& e1) const{
    return prop.getName()==e1.prop.getName();
}
bool Event::operator <(const Event& e1) const{
    return prop.getName()<e1.prop.getName();
}
