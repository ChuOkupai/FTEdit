#include "Distribution.hh"

Weibull::Weibull(QString name) :
Distribution(name)
{}

double Weibull::getScale()
{
	return (value);
}

double Weibull::getShape()
{
	return (shape);
}

double Weibull::getProbability(double time)
{
	// A implémenter
	(void)time;
	return (0);
}

void Weibull::setScale(double scale)
{
	value = scale;
}

void Weibull::setShape(double shape)
{
	this->shape = shape;
}