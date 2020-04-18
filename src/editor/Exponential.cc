#include <cmath>
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
	value = lambda;
}