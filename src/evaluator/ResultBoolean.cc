#include "Evaluator.hh"
#include "ResultBoolean.hh"

ResultBoolean::ResultBoolean(Gate* top,double missionTime,double step,EvalVisitor eval) : Evaluator(top,missionTime,step)
{
}

ResultBoolean::~ResultBoolean(){
    //delete this;
}

//TODO
QList<double> ResultBoolean::getProbabilities(){
    QList<double> result;
    //this->top->accept(this->eval);
    return result;
}
