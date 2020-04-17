#include "Node.hh"


Node::Node() : parent(nullptr), position(0, 0) {}

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
