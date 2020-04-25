#pragma once
#include "Evaluator.hh"


class ResultBoolean : public Evaluator
{
public:
	ResultBoolean(Gate* top, double missionTime,double step);
	~ResultBoolean();
	QList<double> getProbabilities();

	
};