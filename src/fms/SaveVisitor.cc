#include <iostream>
#include <type_traits>
#include "SaveVisitor.hh"

template<typename Base, typename T>
inline bool instanceof(const T* a) {
	return dynamic_cast<const Base*>(a) != nullptr;
}

SaveVisitor::SaveVisitor() {}

SaveVisitor::~SaveVisitor() {}

QDomDocument& SaveVisitor::getDomFile() { return dom; }

void SaveVisitor::writeGateProperties(QDomElement &elem, Gate& gate)
{
	Properties& prop = gate.getProperties();
	elem.setAttribute("name", prop.getName());
	QDomElement tag;
	if(!prop.getDesc().isEmpty())
	{
		tag = dom.createElement("label");
		tag.appendChild(dom.createTextNode(prop.getDesc()));
		elem.appendChild(tag);
	}
}

void SaveVisitor::writeChildren(QDomElement &node, Gate& gate)
{
	QDomElement tmp;
	for(Node* c : gate.getChildren())
	{
		if(instanceof<Gate>(c))
		{
			tmp = dom.createElement("gate");
			tmp.setAttribute("name", (dynamic_cast<Gate*>(c))->getProperties().getName());
		}
		else if(instanceof<Container>(c))
		{
			tmp = dom.createElement("basic-event");
			tmp.setAttribute("name", (dynamic_cast<Container*>(c))->getEvent()->getProperties().getName());
		}
		else if(instanceof<Transfert>(c))
		{
			tmp = dom.createElement("transfert");
			tmp.setAttribute("name", (dynamic_cast<Transfert*>(c))->getLink()->getTop()->getProperties().getName());
		}
		node.appendChild(tmp);
	}
}

void SaveVisitor::writeGate(Gate& gate, QString type)
{
	QDomElement rootgate = dom.createElement("define-gate");
	writeGateProperties(rootgate, gate);
	QDomElement node = dom.createElement(type);
	rootgate.appendChild(node);
	writeChildren(node, gate);
	dom.documentElement().appendChild(rootgate);
}

void SaveVisitor::visit( And &andgate ) { writeGate(andgate, "and"); }

void SaveVisitor::visit( Or &orgate ) { writeGate(orgate, "or"); }

void SaveVisitor::visit( Xor &xorgate ) { writeGate(xorgate, "xor"); }

void SaveVisitor::visit( Inhibit &inhibgate )
{
	QDomElement rootgate = dom.createElement("define-gate");
	writeGateProperties(rootgate, inhibgate);
	QDomElement node = dom.createElement("inhibit");
	QDomElement tmp;
	tmp = dom.createElement("constant");
	tmp.setAttribute("value", inhibgate.getCondition() ? "true" : "false");
	node.appendChild(tmp);
	writeChildren(node, inhibgate);
	rootgate.appendChild(node);
	dom.documentElement().appendChild(rootgate);
}

void SaveVisitor::visit( Transfert &transfertgate ) {(void)transfertgate;/*INUTILE ?!?*/}

void SaveVisitor::visit( Constant &constdistrib ) {(void)constdistrib;}

void SaveVisitor::visit( Exponential &expdistrib ) {(void)expdistrib;}

void SaveVisitor::visit( Weibull &weibulldistrib ) {(void)weibulldistrib;}

void SaveVisitor::visit( Container &container ) {(void)container; /*INUTILE ?!?*/}

void SaveVisitor::visit( Event &event )
{
	QDomElement tag, tag2;
	Properties& prop = event.getProperties(); 
	tag = dom.createElement("define-basic-event");
	tag.setAttribute("name", prop.getName());
	dom.documentElement().appendChild(tag);
	
	// write properties if any
	if(!prop.getDesc().isEmpty())
	{
		tag2 = dom.createElement("label");
		tag2.appendChild(dom.createTextNode(prop.getDesc()));
		tag.appendChild(tag2);
	}
	
	// wrtie parameter if any
	Distribution* distr = event.getDistribution();
	if(distr)
	{
		tag = dom.createElement("parameter");
		tag.setAttribute("name", distr->getProperties().getName());
	}
	dom.documentElement().appendChild(tag);
}
