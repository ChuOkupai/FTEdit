#pragma once
#include "Properties.hh"
#include "Gate.hh"

//class Gate;

class Tree
{
protected:
	Properties	prop;
	Gate		*top;

public:
	Tree(QString name);
	~Tree();

	Properties	&getProperties();
	Gate		*getTop() const;

	void	setTop(Gate *top);
};
