#include "Node.hh"


Node::Node(QPoint position){
    this->position = position; 
}

Gate* Node::getParent(){
  return this->parent;
}

Qpoint Node::getPosition(){
  return this->position; 
}

void Node::setPostion(Qpoint position){
    this->position = position; 
}

void Node::attach(Gate* parent){
    this->parent = parent; 
}

Node* Node::detach(){
  
}
