#pragma once
#include "Distribution.hh"

class Exponential : public Distribution
{
public:
	Exponential(QString name);
	double getLambda() const;
	void setLambda(double lambda);
	double getProbability(double time);
};
