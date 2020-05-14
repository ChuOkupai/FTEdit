#include "Result.hh"
#include <QString>
#include <QList>

Result::Result(Gate* top,bool useMCS,bool useBoolean,double missionTime,double step) : resultMCS(nullptr), resultBoolean(nullptr) {
	
	if(top->check( this->errors ))
	{

		if(useMCS){

			resultMCS = new ResultMCS(top,missionTime,step);
		

		}

		if(useBoolean){

			resultBoolean = new ResultBoolean(top,missionTime,step);
			
		}
	
	}

	this->errors.removeDuplicates();
}

Result::~Result(){
	delete resultBoolean;
	delete resultMCS;

}

QStringList& Result::getErrors(){return errors; }

ResultMCS* Result::getResultMCS(){return this->resultMCS;}

ResultBoolean* Result::getResultBoolean(){return this->resultBoolean;}
