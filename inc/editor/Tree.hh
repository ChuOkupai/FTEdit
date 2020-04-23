#pragma once
#include "Properties.hh"

class Gate;

class Tree
{
private:
	Properties	prop;
	Gate		*top;

public:
	Tree(QString name);
	~Tree();

	Properties	&getProperties();
	Gate		*getTop() const;

	void	setTop(Gate *top);
};
