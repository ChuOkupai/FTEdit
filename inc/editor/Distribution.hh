#pragma once
#include "Properties.hh"

class Distribution
{
protected:
	Properties	prop;
	double		value;

public:
	Distribution(QString name);
	virtual ~Distribution();

	Properties&	getProperties();
	double		getValue();

	void	setValue(double value);

	virtual double	getProbability(double time) = 0;
};

class Constant : public Distribution
{
public:
	Constant(QString name);
	~Constant();

	double	getProbability(double time);
};

class Exponential : public Distribution
{
public:
	Exponential(QString name);
	~Exponential();

	double	getLambda();
	double	getProbability(double time);

	void	setLambda(double lambda);
};

class Weibull : public Distribution
{
private:
	double	shape;
public:
	Weibull(QString name);
	~Weibull();

	double	getScale();
	double	getShape();
	double	getProbability(double time);

	void	setScale(double scale);
	void	setShape(double shape);
};
