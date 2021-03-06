#pragma once
#include "Properties.hh"
#include "Distribution.hh"

class SaveVisitor;

class Event
{
private:
	Properties prop;
	Distribution* distribution ;

public:
	Event(QString name);

	~Event();
	
	Properties& getProperties();
	void setDistribution(Distribution *distribution);
	Distribution* getDistribution();
	void accept(SaveVisitor& v);
	bool operator==(const Event&)const;
	bool operator <(const Event&)const;
};
