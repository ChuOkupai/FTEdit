#pragma once
#include "Evaluator.hh"
#include "EvalVisitor.hh"

class ResultBoolean : public Evaluator
{
public:
	ResultBoolean(Gate* top, double missionTime,double step);
	~ResultBoolean();
};
