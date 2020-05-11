#pragma once
#include <QList>
#include <QPoint>
#include <QString>

#define ICON_RSIZE	80
#define BORDER_SIZE	2
#define CARD_X		(3.5 * ICON_RSIZE)
#define CARD_Y		(3 * ICON_RSIZE)
#define CARD_GAP_Y	(CARD_Y / 2)

// DELETE
#define CARD_GAP_X (CARD_X / 2)

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
	virtual QPoint 	top_node_coord(QPoint cpt) = 0;
	virtual void 	accept(VisitorNode& visitor) = 0;
	virtual double 	accept(EvalVisitor& eval) = 0;
};