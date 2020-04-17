#pragma once
#include <QString>
#include <QList>
#include <QPoint>
#include "Node.hh"
#include "Properties.hh"


class Gate : public Node, public Properties
{
protected:
    Properties prop;
    QList<Node*> children;

private:
    Gate(QString name);
    ~Gate();
    Properties& getProperties();
    QList<Node*>& getChildren();
    Node* search(QPoint around);
};