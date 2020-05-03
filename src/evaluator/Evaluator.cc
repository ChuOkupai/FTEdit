#include "Gate.hh"
#include "Evaluator.hh"


Evaluator::Evaluator(Gate* top,double missionTime, double step)
{
	this->top = top;
	this->missionTime = missionTime;
	this->step = step;
}
Evaluator::~Evaluator(){}
double Evaluator::getMissionTime()
{
	return missionTime;
}
double Evaluator::getStep()
{
	return step;
}
