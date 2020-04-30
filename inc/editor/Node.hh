#pragma once
#include <QList>
#include <QPoint>
#include <QString>
#include <Event.hh>

#define NODE_X	120
#define NODE_Y	80

class Editor;
class Gate;

class Node
{
protected: 
	Gate*	parent;
	QPoint	position;

public:
	Node();
	virtual ~Node();

	Gate*	getParent();
	QPoint	getPosition();
    virtual QList<Node*>&	getChildren() = 0;
    virtual Event& getEvent() = 0;

	void	setPosition(QPoint position);

	void	attach(Gate* parent);
	void	detach();

	virtual Node*	search(QPoint around) = 0;
	virtual double	getProbability(double time) = 0;
	virtual bool	check(QList<QString>& output) = 0;
	virtual void	remove() = 0;
	//virtual void	accept(Editor& editor,EditVisitor& edit) = 0;
	//virtual void	accept(RenderVisitor& visitor) = 0;
};
