#include <QtGlobal>
#include <limits>
#include "Editor.hh"
#include "ClipVisitor.hh"
#include "PasteVisitor.hh"

Editor::Editor(bool autoRefresh) :
clipboard(nullptr), selection(nullptr), autoRefresh(autoRefresh)
{}

Editor::~Editor()
{
	for(int i =0; i< getTrees().size();i++)
	{
		if(getTrees()[i].getTop())
			remove(getTrees()[i].getTop());
	}
	getTrees().clear();
	qDeleteAll(gates);
	getGates().clear();
	getEvents().clear();
	qDeleteAll(distributions);
	getDistributions().clear();
	
	if(clipboard)
		delete clipboard;
	
}

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

void Editor::copy(Node *top)
{
	resetClipboard();
	ClipVisitor tmp;
	top->accept(tmp);
	clipboard = tmp.getCopied();
}

void Editor::cut(Node *top)
{
	
	resetClipboard();
	ClipVisitor tmp;
	top->accept(tmp);
	clipboard = tmp.getCopied();
	top->remove();
}

void Editor::paste(Gate *parent)
{
	if(clipboard)
	{
	PasteVisitor tmp(*this);
	clipboard->accept(tmp);
	tmp.getPasted()->attach(parent);	
	}
}

void Editor::move(Node *child, Gate *parent)
{
	child->detach();
	child->attach(parent);
}

void Editor::remove(Node *top)
{
	if (!top)
		return ;
	top->remove();
	if (selection && top == selection->getTop())
		selection->setTop(nullptr);
	refresh();
}

void Editor::detach(Gate *top)
{
	trees.push_back(Tree(generateName(PREFIX_TREE)));
	trees.last().setTop(top);
	if (selection && top == selection->getTop())
		selection->setTop(nullptr);
	selection = &trees.last();
	if (selection->getTop())
		selection->getTop()->detach();
}

void Editor::join(Tree *child, Gate *parent)
{
	Gate *g = child->getTop();
	if (g)
		g->attach(parent);
	child->setTop(nullptr);
	child->getProperties().setKeep(false);
	refresh();
}

QString Editor::generateName(QString prefix)
{
	QString	s;

	for (uint i = 1; i < std::numeric_limits<uint>::max(); ++i)
		if (isUnique(s = prefix + QString::number(i)))
			return (s);
	return (s = "");
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
	for (int i = 0; i < gates.size(); ++i)
		if (gates[i]->getProperties().getName() == name)
			return (false);
	return (true);
}

void Editor::refresh()
{
	if (!autoRefresh)
		return ;
	for (int i = 0; i < trees.size(); ++i)
		if (trees[i].getProperties().canBeRemoved())
			trees.removeAt(i--);
	for (int i = 0; i < events.size(); ++i)
		if (events[i].getProperties().canBeRemoved())
			events.removeAt(i--);
	for (int i = 0; i < distributions.size(); ++i)
		if (distributions[i]->getProperties().canBeRemoved())
		{
			delete distributions[i];
			distributions.removeAt(i--);
		}
	for (int i = 0; i < gates.size(); ++i)
		if (gates[i]->getProperties().canBeRemoved() && !gates[i]->getParent())
		{
			delete gates[i];
			gates.removeAt(i--);
		}
}

void Editor::resetClipboard()
{
	// détruire la copie de l'arbre dans clipboard
	if(clipboard)
		clipboard->remove();
	clipboard = nullptr;
}