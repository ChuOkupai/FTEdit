#pragma once
#include <QList>
#include <QString>
#include "Gate.hh"



class Evaluator{
	protected : 
		Gate* top;
		double missionTime;
		double step;
		QList<double> probabilities;

	public : 
		Evaluator(Gate* top,double missionTime, double step);
		double getMissionTime();
		double getStep();
        virtual QList<double> getProbabilities() = 0;
		~Evaluator();

};
