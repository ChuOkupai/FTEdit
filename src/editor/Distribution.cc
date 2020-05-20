#include <QtGlobal>
#include "Distribution.hh"

Distribution::Distribution(QString name) : prop(name,false), value(0)
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
	this->value = qBound(0.0, value, 1.0);
}


