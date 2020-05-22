#include <cmath>
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
	value = qBound(0.000000001,lambda,1000000000000.0);
}

void Exponential::accept(VisitorDistribution& visitor)
{
	visitor.visit(*this);
}