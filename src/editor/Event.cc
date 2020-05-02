#include "Event.hh"
#include "FTEdit_FMS.hh"

Event::Event(QString name) : prop(name,false),distribution(nullptr){}

Event::~Event() 
{
	if(this->distribution)
		distribution->getProperties().decrementRefCount();
}

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

bool Event::operator==(const Event& e1) const
{
	return prop.getName() == e1.prop.getName();
}

bool Event:: operator<(const Event& e1) const
{
	return prop.getName()<e1.prop.getName();
}

void Event::accept(SaveVisitor& visitor)
{
	visitor.visit(*this);
}
