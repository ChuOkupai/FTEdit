#pragma once
#include "Properties.hh"

class Gate;

class Tree
{
protected:
	Properties	prop;
	Gate		*top;

public:
	Tree(QString name);
	Tree(const Tree&);
	~Tree();

	Properties	&getProperties();
	Gate		*getTop() const;

	void	setTop(Gate *top);
};
