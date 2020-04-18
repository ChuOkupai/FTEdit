#include <QtGlobal>
#include <limits>
#include "Editor.hh"

Editor::Editor(bool autoRefresh) :
autoRefresh(autoRefresh)
{}

Editor::~Editor()
{}

QList<Tree> &Editor::getTrees()
{
	return (trees);
}

QList<Event> &Editor::getEvents()
{
	return (events);
}

QList<Distribution*> &Editor::getDistributions()
{
	return (distributions);
}

QList<Gate*> &Editor::getGates()
{
	return (gates);
}

Node *Editor::getClipboard()
{
	return (clipboard);
}

Tree *Editor::getSelection()
{
	return (selection);
}

void Editor::setSelection(Tree *selection)
{
	this->selection = selection;
}

void Editor::setAutoRefresh(bool value)
{
	autoRefresh = value;
}

void Editor::refresh()
{
	if (!autoRefresh)
		return ;
}

bool Editor::isUnique(QString name)
{
	for (int i = 0; i < trees.size(); ++i)
		if (trees[i].getProperties().getName() == name)
			return (false);
	for (int i = 0; i < events.size(); ++i)
		if (events[i].getProperties().getName() == name)
			return (false);
	for (int i = 0; i < distributions.size(); ++i)
		if (distributions[i]->getProperties().getName() == name)
			return (false);
	for (int i = 0; i < distributions.size(); ++i)
		if (distributions[i]->getProperties().getName() == name)
			return (false);
	for (int i = 0; i < gates.size(); ++i)
		if (gates[i]->getProperties().getName() == name)
			return (false);
	return (true);
}

QString Editor::generateName(QString prefix)
{
	QString	s;

	for (uint i = 1; i < std::numeric_limits<uint>::max(); ++i)
		if (isUnique(s = prefix + QString::number(i)))
			return (s);
	return (s = "");
}

void Editor::resetClipboard()
{
	;
}

void Editor::copy(Node *top)
{
	(void)top;
}

void Editor::cut(Node *top)
{
	(void)top;
}

void Editor::paste(Gate *parent)
{
	(void)parent;
}

void Editor::move(Node *child, Gate *parent)
{
	(void)child;
	(void)parent;
}

void Editor::remove(Node *top)
{
	(void)top;
}

void Editor::detach(Gate *top)
{
	trees.push_back(Tree(generateName(PREFIX_TREE)));
	trees.last().setTop(top);
	if (top)
	{
		if (top == selection->getTop())
			selection->setTop(nullptr);
		top->detach();
	}
	selection = &trees.last();
}

void Editor::join(Tree *child, Gate *parent)
{
	Gate *g = child->getTop();
	parent->attach(g);
	child->setTop(nullptr);
	child->getProperties().setKeep(false);
	refresh();
}