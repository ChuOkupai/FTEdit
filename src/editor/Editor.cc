#include <QtGlobal>
#include <limits>
#include "Editor.hh"
#include "CopyVisitor.hh"

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
	getGates().clear();
	getEvents().clear();
	getDistributions().clear();
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
	CopyVisitor tmp;
	top->accept(tmp);
	clipboard = tmp.getCopied();
}

void Editor::cut(Node *top)
{
	
	resetClipboard();
	CopyVisitor tmp;
	top->accept(tmp);
	clipboard = tmp.getCopied();
	top->remove();
}

void Editor::remove_duplicate_names(Node* top)
{
	if(dynamic_cast<Gate*>(top))
	{
		Gate* tmp = dynamic_cast<Gate*>(top);
			if(!isUnique(tmp->getProperties().getName()))
			{
				tmp->getProperties().setName(generateName(PREFIX_GATE));
				getGates()<<tmp;
			}
			for(int i =0; i<tmp->getChildren().size();i++)
			{
				remove_duplicate_names(tmp->getChildren()[i]);
			}

	}
	if(dynamic_cast<Transfert*>(top))
	{
		Transfert* tmp = dynamic_cast<Transfert*>(top);
			if(!isUnique(tmp->getLink()->getProperties().getName()))
			{
				tmp->getLink()->getProperties().setName(generateName(PREFIX_TREE));
			}
		remove_duplicate_names(tmp->getLink()->getTop());
	}
	if(dynamic_cast<Container*>(top))
	{
		Container* tmp = dynamic_cast<Container*>(top);

			if(!isUnique(tmp->getEvent()->getProperties().getName()))
			{
				tmp->getEvent()->getProperties().incrementRefCount();
			}
			else
			{
				getEvents()<<*(tmp->getEvent());	
			}
			if(tmp->getEvent()->getDistribution())
			{
				if(!isUnique(tmp->getEvent()->getDistribution()->getProperties().getName()))
				{
					tmp->getEvent()->getDistribution()->getProperties().incrementRefCount();
				}
				else
				{
					getDistributions()<<tmp->getEvent()->getDistribution();
				}
			}
	}
}

void Editor::paste(Gate *parent)
{
	CopyVisitor tmp;
	clipboard->accept(tmp);
	remove_duplicate_names(tmp.getCopied());
	tmp.getCopied()->attach(parent);	
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
	top->detach();
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
}

void Editor::join(Tree *child, Gate *parent)
{
	Gate *g = child->getTop();
	parent->attach(g);
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
}