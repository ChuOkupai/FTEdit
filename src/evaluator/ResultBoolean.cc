#include "Evaluator.hh"
#include "ResultBoolean.hh"

ResultBoolean::ResultBoolean(Gate* top,double missionTime,double step) : Evaluator(top,missionTime,step)
{
	this->topEventName = top->getProperties().getName();
	EvalVisitor eval;
	for(double i = 0; i < this->missionTime; i = i + this->step){
		this->probabilities << eval.getProba(top,i);
	}
}

ResultBoolean::~ResultBoolean(){
}

QString ResultBoolean::getTopEventName(){
	return topEventName;
}
