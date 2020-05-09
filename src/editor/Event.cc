#include "Event.hh"
#include "SaveVisitor.hh"

Event::Event(QString name) : prop(name,false), distribution(nullptr)
{}

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

void Event::accept(SaveVisitor& v)
{
	v.visit(*this);
}

bool Event::operator==(const Event& e1) const
{
	return prop.getName()  == e1.prop.getName();
}

bool Event::operator <(const Event& e1) const
{
	return prop.getName()<e1.prop.getName();
}


