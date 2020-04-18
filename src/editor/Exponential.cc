#include <cmath>
#include <QtGlobal>
#include "Distribution.hh"

Exponential::Exponential(QString name) :
Distribution(name)
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
	value = qBound(0.0, lambda, 1.0);
}