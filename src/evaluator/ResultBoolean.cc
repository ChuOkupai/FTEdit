#include "ResultBoolean.hh"

ResultBoolean::ResultBoolean(Gate* top,double missionTime,double step) : Evaluator(top,missionTime,step)
{
	EvalVisitor eval;

	if (this->missionTime)
		for(double i = 0; i <= this->missionTime; i = i + this->step)
			this->probabilities << eval.getProba(top,i);
	else
		this->probabilities << eval.getProba(top, 0);
}

ResultBoolean::~ResultBoolean(){
}
