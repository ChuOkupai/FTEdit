#pragma once
#include "Properties.hh"

class Distribution
{
protected:
	Properties	prop;
	double		value;

public:
	Distribution(QString name);
	~Distribution();

	Properties&	getProperties();
	double		getValue();

	void	setValue(double value);

	virtual double	getProbability(double time) = 0;
};
