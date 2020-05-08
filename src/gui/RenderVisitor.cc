#include "RenderVisitor.hh"

RenderVisitor::RenderVisitor(GraphicsView *view, Tree *tree) :
view(view), scene(view->scene())
{
	(void)this->view;
	scene->clear();
	view->update();
	qDebug() << "\nRender;";
	if (tree->getTop())
		tree->getTop()->accept(*this);
}

void RenderVisitor::visitChildren(Gate &gate)
{
	QList<Node*> &children = gate.getChildren();
	QList<Node*>::const_iterator i;
	for (i = children.constBegin(); i != children.constEnd(); ++i)
		(*i)->accept(*this);
}

void RenderVisitor::visit(And &gate)
{
	qDebug() << "AND gate: " << gate.getProperties().getName();
	visitChildren(gate);
}

void RenderVisitor::visit(Or &gate)
{
	qDebug() << "OR gate: " << gate.getProperties().getName();
	visitChildren(gate);
}

void RenderVisitor::visit(Xor &gate)
{
	qDebug() << "XOR gate: " << gate.getProperties().getName();
	visitChildren(gate);
}

void RenderVisitor::visit(VotingOR &gate)
{
	qDebug() << "Voting OR gate: " << gate.getProperties().getName();
	visitChildren(gate);
}

void RenderVisitor::visit(Inhibit &gate)
{
	qDebug() << "Inhibit gate: " << gate.getProperties().getName();
	visitChildren(gate);
}

void RenderVisitor::visit(Transfert &gate)
{
	QString s = gate.getLink() ? gate.getLink()->getProperties().getName() : "no link";
	qDebug() << "Transfert gate: " << s;
}

void RenderVisitor::visit(Container &cont)
{
	qDebug() << "Event: " << cont.getEvent()->getProperties().getName();
}