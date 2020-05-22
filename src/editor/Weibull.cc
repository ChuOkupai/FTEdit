#include <cmath>
#include <limits>
#include <QtGlobal>
#include "Distribution.hh"
#include "VisitorDistribution.hh"

Weibull::Weibull(QString name) : Distribution(name), shape(0)
{}

Weibull::~Weibull()
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
	return(1-exp(-pow((time/value),shape)));
}

void Weibull::setScale(double scale)
{
	value = qBound(0.0,scale,std::numeric_limits<double>::max());
}

void Weibull::setShape(double shape)
{
	this->shape = qBound(0.0,shape,std::numeric_limits<double>::max());
}

void Weibull::accept(VisitorDistribution& visitor)
{
	visitor.visit(*this);
}