#include <cmath>
#include <QtGlobal>
#include "Distribution.hh"
#include "FTEdit_FMS.hh"

Weibull::Weibull(QString name) :
Distribution(name)
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
	return (1-exp(-pow((time/value),shape)));
}

void Weibull::setScale(double scale)
{
	value = scale;
}

void Weibull::setShape(double shape)
{
	this->shape = shape;
}

void Weibull::accept(SaveVisitor& visitor)
{
	visitor.visit(*this);
}