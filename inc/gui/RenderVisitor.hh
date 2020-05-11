#pragma once
#include "FTEdit_Editor.hh"
#include "MainWindow.hh"
#include "WidgetLinker.hh"

// Qt graphic item (Node has to be converted)
class NodeItem : public QGraphicsRectItem
{
private:
	QMenu *contextMenu;
	QPixmap icon;
	Node *n;
	Properties *prop;
	bool child;

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

public:
	NodeItem(QMenu *contextMenu, QPixmap icon, Node *n, Properties *prop, bool isChild = false);

	bool isChild();

	// GetNode
	Node *node();

	void setProperties(Properties *prop);

	QRectF boundingRect() const override;

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