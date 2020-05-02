#include "Event.hh"
#include "FTEdit_FMS.hh"

Event::Event(QString name) : prop(name),distribution(nullptr){}

Event::~Event() {}

void Event::setDistribution(Distribution *distribution)
{
	if (this->distribution)//decrement if distribution not null
		this->distribution->getProperties().decrementRefCount();
	this->distribution = distribution;
	if(this->distribution)//increment if distribution not null
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

void Event::accept(SaveVisitor& visitor)
{
	visitor.visit(*this);
}
