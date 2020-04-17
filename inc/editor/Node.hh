#pragma once
#include <QList>
#include <QPoint>
#include <QString>
#include "Gate.hh"

#define NODE_X	120
#define NODE_Y	80

class Node{
	protected : 
		Gate* parent;
		QPoint position;

	private :
		Node();
		Gate* getParent();
		QPoint getPosition();
		void setPosition(QPoint position);
		void attach(Gate* parent);
		Node* detach();
		Node* search(QPoint around) = 0;
		virtual double getProbability(double time) = 0;
		virtual bool check(QList<QString>& output) = 0;
		virtual void accept(Editor& editor,EditVisitor& edit) = 0;
		virtual void accept(RenderVisitor& visitor) = 0;
		virtual ~Node();
};
