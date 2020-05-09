#pragma once
#include "FTEdit_Editor.hh"
#include "MainWindow.hh"
#include "WidgetLinker.hh"

#define ICON_RSIZE	80
#define BORDER_SIZE	2
#define CARD_X		(3 * ICON_RSIZE)
#define CARD_Y		(3 * ICON_RSIZE)
#define CARD_GAPY	(CARD_Y / 2)

// Qt graphic item (Node has to be converted)
class NodeItem : public QGraphicsRectItem
{
private:
	QMenu *contextMenu;
	QPixmap icon;
	Node *n;
	Properties *prop;
	bool child;

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

public:
	NodeItem(QMenu *contextMenu, QPixmap icon, Node *n, Properties *prop, bool isChild = false);

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
	MainWindow &win;
	Node *selection;

public:
	RenderVisitor(MainWindow &win, Node *selection);

	void visit(And &gate);

	void visit(Or &gate);

	void visit(Xor &gate);

	void visit(VotingOR &gate);

	void visit(Inhibit &gate);

	void visit(Transfert &gate);

	void visit(Container &cont);
};