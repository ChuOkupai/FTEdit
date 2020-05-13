#pragma once
#include <QStringList>
#include "ResultMCS.hh"
#include "ResultBoolean.hh"

class Result
{
	private :
		QStringList errors;
		ResultMCS *resultMCS;
		ResultBoolean *resultBoolean;

	public:
		Result(Gate* top, bool useMCS,bool useBoolean,double missionTime,double step);
		~Result();
		QStringList& getErrors();
		ResultMCS* getResultMCS();
		ResultBoolean *getResultBoolean();
	
};
