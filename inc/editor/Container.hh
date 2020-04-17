#pragma once
#ifndef CONTAINER_HH
# define CONTAINER_HH
# include <QString>
# include <QPoint>
# include "Node.hh"
# include "Event.hh"
# include "Editor.hh"

class Container : public Node
{
private:
    Event& event = nullptr;

public:
    Container(Event &event);

    ~Container();
    
    void setEvent(Event &event);
    
    double getProbability(double time);
    
    Event& getEvent();

    bool check(QList<QString> &errors);

    Node* search(QPoint around);
    
    void accept(Editor &editor, EditVisitor &visitor);
    
    void accept(RenderVisitor &visitor);
};

#endif
