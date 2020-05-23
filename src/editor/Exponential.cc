#include <cmath>
#include <limits>
#include <QtGlobal>
#include "Distribution.hh"
#include "VisitorDistribution.hh"

Exponential::Exponential(QString name) : Distribution(name)
{}

Exponential::~Exponential()
{}

double Exponential::getLambda()
{
	return (value);
}

double Exponential::getProbability(double time)
{
	return (1 - exp(-value * time));
}

void Exponential::setLambda(double lambda)
{
	value = qBound(0.0,lambda,std::numeric_limits<double>::max());
}

void Exponential::accept(VisitorDistribution& visitor)
{
	visitor.visit(*this);
}