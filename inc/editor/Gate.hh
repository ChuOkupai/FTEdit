#pragma once
#include <QList>
#include "Node.hh"
#include "Properties.hh"

class Gate : public Node
{
protected:
	Properties prop;
	QList<Node*> children;

public:
	Gate(QString name);
	~Gate();
	Properties& getProperties();
	QList<Node*>& getChildren();
	Node* search(QPoint around);
};