#pragma once
#include "Properties.hh"
#include "Distribution.hh"

class Event
{
private:
	Properties prop;
	Distribution* distribution = nullptr;

public:
	Event(QString name);

	~Event();
	
	Properties& getProperties();

	void setDistribution(Distribution *distribution);
	
	Distribution* getDistribution();
};
