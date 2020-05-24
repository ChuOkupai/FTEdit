#include <iostream>
#include <type_traits>
#include <QDebug>
#include "SaveVisitor.hh"
#include "FileManagerSystem.hh"

template<typename Base, typename T>
inline bool instanceof(const T* a) {
	return dynamic_cast<const Base*>(a) != nullptr;
}

SaveVisitor::SaveVisitor() {}

SaveVisitor::~SaveVisitor() {}

void SaveVisitor::setTreeElem(QDomElement elem) { treeElem = elem; }

QDomDocument& SaveVisitor::getDomFile() { return dom; }

void SaveVisitor::writeNameLabel(QDomElement &elem, Properties& prop)
{
	elem.setAttribute("name", prop.getName());
	QDomElement tag, attrs;
	if(!prop.getDesc().isEmpty())
	{
		tag = dom.createElement("label");
		tag.appendChild(dom.createTextNode(prop.getDesc()));
		elem.appendChild(tag);
	}
}

void SaveVisitor::writeKeep(QDomElement &propelem, Properties& prop)
{
	QDomElement tag = dom.createElement("attribute");
	tag.setAttribute("name", "keep");
	tag.setAttribute("value", prop.getKeep() ? "true" : "false");
	propelem.appendChild(tag);
}

void SaveVisitor::writeTypeDistrib(QDomElement &node, QString type)
{
	QDomElement typelem = dom.createElement("attribute");
	typelem.setAttribute("name", "type");
	typelem.setAttribute("value", type);
	node.appendChild(typelem);
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
			tmp = dom.createElement("gate");
			Transfert* transfert = dynamic_cast<Transfert*>(c);
			if(transfert != nullptr && transfert->getLink() != nullptr)
				tmp.setAttribute("name", transfert->getLink()->getProperties().getName());
		}
		node.appendChild(tmp);
	}
}

void SaveVisitor::writeGate(Gate& gate, QString type)
{
	QDomElement rootgate = dom.createElement("define-gate");
	Properties& prop = gate.getProperties();
	writeNameLabel(rootgate, prop);
	QDomElement node = dom.createElement(type);
	rootgate.appendChild(node);
	writeChildren(node, gate);
	treeElem.appendChild(rootgate);
}

void SaveVisitor::visit( And &andgate ) { writeGate(andgate, "and"); }

void SaveVisitor::visit( Or &orgate ) { writeGate(orgate, "or"); }

void SaveVisitor::visit( Xor &xorgate ) { writeGate(xorgate, "xor"); }

void SaveVisitor::visit( VotingOR &vorgate )
{ 
	QDomElement rootgate = dom.createElement("define-gate");
	Properties& prop = vorgate.getProperties();
	writeNameLabel(rootgate, prop);
	QDomElement node = dom.createElement("atleast");
	node.setAttribute("min", vorgate.getK());
	rootgate.appendChild(node);
	writeChildren(node, vorgate);
	treeElem.appendChild(rootgate);
}

void SaveVisitor::visit( Inhibit &inhibgate )
{
	QDomElement rootgate = dom.createElement("define-gate");
	Properties& prop = inhibgate.getProperties();
	writeNameLabel(rootgate, prop);
	QDomElement node = dom.createElement("and");
	QDomElement tmp;
	tmp = dom.createElement("constant");
	tmp.setAttribute("value", inhibgate.getCondition() ? "true" : "false");
	node.appendChild(tmp);
	writeChildren(node, inhibgate);
	rootgate.appendChild(node);
	treeElem.appendChild(rootgate);
}

void SaveVisitor::visit( Constant &constdistrib )
{
	QDomElement distr = dom.createElement("define-parameter");
	Properties& prop = constdistrib.getProperties();
	distr.setAttribute("name", prop.getName());

	QDomElement propelem = dom.createElement("attributes");
	writeNameLabel(distr, prop);
	writeKeep(propelem, prop);
	writeTypeDistrib(propelem, "const");
	distr.appendChild(propelem);

	QDomElement val = dom.createElement("float");
	val.setAttribute("value", doubleToString(constdistrib.getValue()));
	qDebug() << doubleToString(0.00001);
	distr.appendChild(val);
	dom.documentElement().appendChild(distr);
}

void SaveVisitor::visit( Exponential &expdistrib )
{
	//Même nombre de valeur
	QDomElement distr = dom.createElement("define-parameter");
	Properties& prop = expdistrib.getProperties();
	distr.setAttribute("name", prop.getName());

	QDomElement propelem = dom.createElement("attributes");
	writeNameLabel(distr, prop);
	writeKeep(propelem, prop);
	writeTypeDistrib(propelem, "exp");
	distr.appendChild(propelem);

	QDomElement val = dom.createElement("float");
	val.setAttribute("value", doubleToString(expdistrib.getValue()));
	distr.appendChild(val);
	dom.documentElement().appendChild(distr);
}

void SaveVisitor::visit( Weibull &weibulldistrib )
{
	QDomElement distr = dom.createElement("define-parameter");
	Properties& prop = weibulldistrib.getProperties();
	QDomElement propelem = dom.createElement("attributes");
	writeNameLabel(distr, prop);
	writeKeep(propelem, prop);
	writeTypeDistrib(propelem, "weibull");
	distr.appendChild(propelem);

	QDomElement val;
	val = dom.createElement("float");
	val.setAttribute("value", doubleToString(weibulldistrib.getScale()));
	distr.appendChild(val);
	val = dom.createElement("float");
	val.setAttribute("value", doubleToString(weibulldistrib.getShape()));
	distr.appendChild(val);
	dom.documentElement().appendChild(distr);
}

void SaveVisitor::visit( Event &event )
{
	QDomElement tag, tag2;
	Properties& prop = event.getProperties(); 
	tag = dom.createElement("define-basic-event");
	QDomElement propelem = dom.createElement("attributes");
	writeNameLabel(tag, prop);
	writeKeep(propelem, prop);
	tag.appendChild(propelem);
	
	// wrtie parameter if any
	Distribution* distr = event.getDistribution();
	if(distr)
	{
		tag2 = dom.createElement("parameter");
		tag2.setAttribute("name", distr->getProperties().getName());
		tag.appendChild(tag2);
	}
	dom.documentElement().appendChild(tag);
}

void SaveVisitor::visit( Transfert &transfertgate ) { (void)transfertgate; }
void SaveVisitor::visit( Container &container ) { (void)container; }

QString doubleToString(double d)
{
	QLocale loc("C");
	QString s(loc.toString(d, 'f', 12));
	int start = s.indexOf(loc.decimalPoint()) + 2, end = s.size(), i = end - 1;
	while (i > start && s[i] == '0')
		--i;
	i += s[i] != '0';
	return (s.remove(i, end - i));
}

