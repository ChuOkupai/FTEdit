#pragma once

#ifndef NODE_HH
#define NODE_HH
#include <list>
#include <QPoint>
#include <QString>
#include <iostream>

class Node{
  protected : 
    Gate* parent;
    QPoint position;
  
  private :
    Node(QPoint position);
    Gate* getParent();
    QPoint getPosition();
    void setPosition(QPoint position);
    void attach(Gate* parent);
    Node* detach();
    Node* virtual search(QPoint around) = 0;
    double virtual getProbability(double time) = 0;
    bool virtual check(list<QString>& output) = 0;
    void virtual accept(Editor& editor,EditVisitor& edit) = 0;
    void virtual accept(RenderVisitor& visitor) = 0;
  
}

#endif
