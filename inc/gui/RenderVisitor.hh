#pragma once
#include "FTEdit_Editor.hh"
#include "WidgetLinker.hh"

#define ICON_RSIZE 80
#define BORDER_SIZE 2
#define CARD_X (3 * ICON_RSIZE)
#define CARD_Y (3 * ICON_RSIZE)
#define CARD_GAPX (CARD_Y / 2)
#define CARD_GAPY (CARD_Y / 2)

class NodeItem : public QGraphicsItem
{
private:
	QPixmap icon;
	bool pressed;

protected:
	Node *n;
	Properties *prop;

	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

public:
	NodeItem(Node *n, Properties *prop, QPixmap icon);

	QRectF boundingRect() const;

	Node *getNode();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class RenderVisitor : public VisitorNode
{
private:
	QGraphicsScene *scene;

public:
	RenderVisitor(GraphicsView *view,  Tree *tree);

	void visit(And &gate);

	void visit(Or &gate);

	void visit(Xor &gate);

	void visit(VotingOR &gate);

	void visit(Inhibit &gate);

	void visit(Transfert &gate);

	void visit(Container &cont);
};