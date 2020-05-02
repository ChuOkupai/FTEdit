#include "Evaluator.hh"
#include "ResultBoolean.hh"

ResultBoolean::ResultBoolean(Gate* top,double missionTime,double step) : Evaluator(top,missionTime,step)
{
    this->topEventName = top->getProperties().getName();
}

ResultBoolean::~ResultBoolean(){
}

//TODO
QList<double> ResultBoolean::getProbabilities(){
    EvalVisitor eval = new EvalVisitor(0,0);
    for(int i = 0; i < missionTime; i = i + step){
        eval.setTime(i);
        top->accept(eval);
        this->probabilities.insert(i,eval.getProba());
        eval.reset();
    }
    delete eval;
    return probabilities;;
}

QString ResultBoolean::getTopEventName(){
    return topEventName;
}
