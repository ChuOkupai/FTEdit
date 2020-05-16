#pragma once
#include "Evaluator.hh"
#include "EvalVisitor.hh"

class ResultBoolean : public Evaluator
{
private :

public:
	ResultBoolean(Gate* top, double missionTime,double step);
	~ResultBoolean();
	
};
