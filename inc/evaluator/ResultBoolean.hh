#pragma once
#include "Evaluator.hh"
#include "EvalVisitor.hh"


class ResultBoolean : public Evaluator
{
	private :
	EvalVisitor eval;
public:
	ResultBoolean(Gate* top, double missionTime,double step,EvalVisitor eval);
	~ResultBoolean();
	QList<double> getProbabilities();

	
};