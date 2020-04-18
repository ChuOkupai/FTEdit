#include "Distribution.hh"

Distribution::Distribution(QString name) :
prop(name)
{}

Distribution::~Distribution()
{}

Properties& Distribution::getProperties()
{
	return (prop);
}

double Distribution::getValue()
{
	return (value);
}

void Distribution::setValue(double value)
{
	this->value = value;
}


