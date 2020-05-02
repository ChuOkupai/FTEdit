#pragma once
#include "Editor.hh"

class Visitor;

class Container : public Node
{
private:
	Event *event;

public:
	Container(Event *event);

	~Container();
	
	void	setEvent(Event *event);
	
	double	getProbability(double time);
	
	Event	*getEvent();

	bool	check(QList<QString> &errors);
	Node*	search(QPoint around);
	void	remove();
	void	accept(Visitor& visitor);
};
