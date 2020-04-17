#pragma once

#include <QString>
#include "Properties.hh"

class Distribution
{
	protected:
		Properties prop;
		double value;
	public:
		Distribution(QString name);
		Properties& getProperties();
		double getValue();
		void setValue();
		virtual double getProbability(double time) = 0;
};
