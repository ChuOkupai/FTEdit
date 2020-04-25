#pragma once
#include "ResultMCS.hh"
#include "ResultBoolean.hh"



class Result
{
	private :
	QList<QString> errors;
	ResultMCS *resultMCS;
    ResultBoolean *resultBoolean;

	public:
	Result(Gate* top, bool useMCS,bool useBoolean);
	~Result();
	QList<QString>& getErrors();
	ResultMCS* getResultMCS();
    ResultBoolean *getResultBoolean();
	
};
