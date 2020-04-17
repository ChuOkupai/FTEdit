#pragma once

#include "Distribution.hh"

class Exponential : public Distribution
{
	public:
		Exponential(QString name);
		const double getLambda();
		void setLambda(double lambda);
		double getProbability(double time);
};
