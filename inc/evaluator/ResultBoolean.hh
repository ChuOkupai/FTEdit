#pragma once
#include "Evaluator.hh"
#include "EvalVisitor.hh"


class ResultBoolean : public Evaluator
{
	private :
		QString topEventName;
	
	public:
		ResultBoolean(Gate* top, double missionTime,double step,EvalVisitor eval);
		~ResultBoolean();
		QString getTopEventName();
		QList<double> getProbabilities();

	
};