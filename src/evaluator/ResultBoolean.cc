#include "Evaluator.hh"
#include "ResultBoolean.hh"

ResultBoolean::ResultBoolean(Gate* top,double missionTime,double step) : Evaluator(top,missionTime,step)
{
}

ResultBoolean::~ResultBoolean(){
    //delete this;
}

//TODO
QList<double> ResultBoolean::getProbabilities(){
    //this->top->accept(this->eval);
    return probabilities;;
}

QString ResultBoolean::getTopEventName(){
    return topEventName;
}