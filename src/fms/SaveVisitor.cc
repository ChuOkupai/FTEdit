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

void SaveVisitor::visit( And &andgate )
{ 
	QDomElement rootgate = dom.createElement("define-gate");
	writeGateProperties(rootgate, andgate);
	QDomElement andnode = dom.createElement("and");
	rootgate.appendChild(andnode);
	QDomElement tmp;
	for(Node* c : andgate.getChildren())
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
		andnode.appendChild(tmp);
	}
	dom.documentElement().appendChild(rootgate);
}

void SaveVisitor::visit( Or &orgate ) { (void)orgate;}

void SaveVisitor::visit( Xor &xorgate ) {(void)xorgate; }

void SaveVisitor::visit( Inhibit &inhibgate ) {(void)inhibgate;}

void SaveVisitor::visit( Transfert &transfertgate ) {(void)transfertgate;}

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

	// write properties ...
	tag2 = dom.createElement("label");
	tag2.appendChild(dom.createTextNode(prop.getDesc()));
	tag.appendChild(tag2);
	// wrtie parameter if any
	Distribution* distr = event.getDistribution();
	if(distr)
	{
		tag = dom.createElement("parameter");
		tag.setAttribute("name", distr->getProperties().getName());
	}
	dom.documentElement().appendChild(tag);
}

void SaveVisitor::writeGateProperties(QDomElement &elem, Gate& gate)
{
	Properties& prop = gate.getProperties();
	elem.setAttribute("name", prop.getName());
	QDomElement tag;
	tag = dom.createElement("label");
	tag.appendChild(dom.createTextNode(prop.getDesc()));
	elem.appendChild(tag);
	tag = dom.createElement("attributes");
	elem.appendChild(tag);
	tag = dom.createElement("attribute");
	tag.setAttribute("x", gate.getPosition().x());
	elem.lastChild().appendChild(tag);
	tag = dom.createElement("attribute");
	tag.setAttribute("y", gate.getPosition().y());
	elem.lastChild().appendChild(tag);
}
