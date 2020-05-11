#pragma once
#include "Evaluator.hh"
#include "EvalVisitor.hh"

class ResultBoolean : public Evaluator
{
private :
	QString topEventName;

public:
	ResultBoolean(Gate* top, double missionTime,double step);
	virtual ~ResultBoolean();
	QString getTopEventName();
	QList<double> getProbabilities();
	
};
