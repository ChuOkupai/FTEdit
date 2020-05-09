#pragma once
#include "FTEdit_Editor.hh"
#include "MainWindow.hh"
#include "WidgetLinker.hh"

#define ICON_RSIZE 80
#define BORDER_SIZE 2
#define CARD_X (3 * ICON_RSIZE)
#define CARD_Y (3 * ICON_RSIZE)
#define CARD_GAPX (CARD_Y / 2)
#define CARD_GAPY (CARD_Y / 2)

// Qt graphic item (Node has to be converted)
class NodeItem : public QGraphicsRectItem
{
private:
	Editor &editor;
	QPixmap icon;
	Node *n;
	Properties *prop;
	bool child;
	bool pressed;

	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

public:
	NodeItem(Editor &editor, QPixmap icon, Node *n, Properties *prop, bool isChild = false);

	bool isChild();

	// GetNode
	Node *node();

	void setProperties(Properties *prop);

	QRectF boundingRect() const;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class RenderVisitor : public VisitorNode
{
private:
	QGraphicsScene *scene;
	Editor &editor;
	Node *selection;

public:
	RenderVisitor(QGraphicsScene *scene, Editor &editor, Node *selection);

	void visit(And &gate);

	void visit(Or &gate);

	void visit(Xor &gate);

	void visit(VotingOR &gate);

	void visit(Inhibit &gate);

	void visit(Transfert &gate);

	void visit(Container &cont);
};