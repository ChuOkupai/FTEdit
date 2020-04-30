
#include "ResultMCS.hh"

ResultMCS::ResultMCS(Gate* top,double missionTime,double step) : Evaluator(top,missionTime,step)
{


}

ResultMCS::~ResultMCS(){}

void ResultMCS::computeCS(){

}

void ResultMCS::reduceCS(){}

void ResultMCS::sortCut(){}

void ResultMCS::sieveOfAtkin(int n){}

void ResultMCS::convertCS(QList<QList<Node*>> cs){

}

QList<QList<Event>> ResultMCS::getMCS(){
    return mcs;
}
QList<double> ResultMCS::getProbabilities(){
    
    return probabilities;

}
