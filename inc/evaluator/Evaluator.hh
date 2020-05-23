#pragma once
#include <QList>
#include "Gate.hh"

class Evaluator{
protected : 
	Gate* top;
	double missionTime;
	double step;
	QList<double> probabilities;

public : 
	Evaluator(Gate* top,double missionTime, double step);
	virtual ~Evaluator();
	double getMissionTime();
	double getStep();
	QList<double> getProbabilities();
    QString getTopEventName();
};
