#include <cmath>
#include <QtGlobal>
#include "Distribution.hh"
#include "../fms/SaveVisitor.hh"

Exponential::Exponential(QString name) :
Distribution(name)
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
	value = qBound(0.0, lambda, 1.0);
}

void Exponential::accept(SaveVisitor& visitor)
{
	visitor.visit(*this);
}