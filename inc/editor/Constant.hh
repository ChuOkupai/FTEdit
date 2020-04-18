#pragma once
#include "Distribution.hh"

class Constant : public Distribution
{
public:
	Constant(QString name);

	double	getProbability(double time);
};
