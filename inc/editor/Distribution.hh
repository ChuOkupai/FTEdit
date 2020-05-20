#pragma once
#include "Properties.hh"

class VisitorDistribution;

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
	virtual void 	accept(VisitorDistribution& visitor) = 0;
};

class Constant : public Distribution
{
public:
	Constant(QString name);
	~Constant();

	double	getProbability(double time);
	void 	accept(VisitorDistribution& visitor);
};

class Exponential : public Distribution
{
public:
	Exponential(QString name);
	~Exponential();

	double	getLambda();
	double	getProbability(double time);
	void	setLambda(double lambda);
	void 	accept(VisitorDistribution& visitor);
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
	void	accept(VisitorDistribution& visitor);
};
