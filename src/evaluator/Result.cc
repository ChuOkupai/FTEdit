#include "Result.hh"
#include <QString>
#include <QList>

Result::Result(Gate* top,bool useMCS,bool useBoolean,double missionTime,double step){
    if(!top->check( this->errors )){

    }else{
    if(useMCS){
        resultMCS = new ResultMCS(top,missionTime,step);

    }
    if(useBoolean){
        resultBoolean = new ResultBoolean(top,missionTime,step);
    }
    }
}

Result::~Result(){delete this;}

QList<QString>& Result::getErrors(){return errors; }

ResultMCS* Result::getResultMCS(){return this->resultMCS;}

ResultBoolean* Result::getResultBoolean(){return this->resultBoolean;}
