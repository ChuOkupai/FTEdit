#pragma once
#include "FTEdit_Editor.hh"
#include "WidgetLinker.hh"

class RenderVisitor : public VisitorNode
{
private:
	GraphicsView	*view;
	QGraphicsScene	*scene;

public:
	RenderVisitor(GraphicsView *view,  Tree *tree);

	void visitChildren(Gate &gate);

	void visit(And &gate);

	void visit(Or &gate);

	void visit(Xor &gate);

	void visit(VotingOR &gate);

	void visit(Inhibit &gate);

	void visit(Transfert &gate);

	void visit(Container &cont);
};