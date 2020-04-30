#include "Result.hh"
#include <QString>
#include <QList>

Result::Result(Gate* top,bool useMCS,bool useBoolean,double missionTime,double step){
    if(useMCS){
        resultMCS = new ResultMCS(top,missionTime,step);

    }
    if(useBoolean){
        EvalVisitor eval ;
        resultBoolean = new ResultBoolean(top,missionTime,step,eval);

    }

}

Result::~Result(){
    delete this;
}

QList<QString>& Result::getErrors(){
    QList<QString>* qq = new QList<QString>;

    return *qq;
    
}

ResultMCS* Result::getResultMCS(){
    if(this->resultMCS != nullptr){
        return this->resultMCS;
    }
    return nullptr;
}

ResultBoolean* Result::getResultBoolean(){
    if(this->resultBoolean != nullptr){
        return this->resultBoolean;
    }
    return nullptr;
}
