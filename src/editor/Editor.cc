#include <QtGlobal>
#include <limits>
#include "Editor.hh"

Editor::Editor(bool autoRefresh) : autoRefresh(autoRefresh) {};

QList<Tree> &Editor::getTrees() const
{
	return (trees);
}

QList<Event> &Editor::getEvents() const
{
	return (events);
}

QList<Distribution> &Editor::getDistributions() const
{
	return (distributions);
}

QList<Gate> &Editor::getGates() const
{
	return (gates);
}

Node *Editor::getClipboard() const
{
	return (clipboard);
}

Tree *Editor::getSelection() const
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
	;
}

bool Editor::isUnique(QString name)
{
	;
}

QString	Editor::generateName(QString prefix)
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

void Editor::paste(Node *top)
{
	(void)top;
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

void Editor::detach(Node *top)
{
	(void)top;
}

void Editor::join(Tree *child, Gate *parent)
{
	(void)child;
	(void)parent;
}