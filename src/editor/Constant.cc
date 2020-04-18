#include "Distribution.hh"

Constant::Constant(QString name) :
Distribution(name)
{}

Constant::~Constant()
{}

double Constant::getProbability(double time)
{
	(void)time;
	return (value);
}
