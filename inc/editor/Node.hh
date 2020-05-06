#pragma once
#include <QList>
#include <QPoint>
#include <QString>

#define NODE_X	120
#define NODE_Y	80

class Editor;
class Gate;
class VisitorNode;
class EvalVisitor;

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

	void	setPosition(QPoint position);

	void	attach(Gate* parent);
	void	detach();

	virtual Node*	search(QPoint around) = 0;
	virtual bool	check(QList<QString>& output) = 0;
	virtual void	remove() = 0;
	virtual void 	balanceNodePos() = 0;
	virtual void 	accept(VisitorNode& visitor) = 0;
	virtual double 	accept(EvalVisitor& eval) = 0;
};