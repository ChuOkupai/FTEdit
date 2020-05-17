#include <QDebug>
#include "XmlTreeReader.hh"

XmlTreeReader::XmlTreeReader(QFile *f, Editor* e) : e(e) ,nodelistcursor(0) { dom.setContent(f);}

XmlTreeReader::~XmlTreeReader() {}

void XmlTreeReader::read()
{
	QList<QDomElement> lparams;
	QList<QDomElement> ltree;
	QList<QDomElement> levents;
	
	QDomElement root=dom.documentElement();

	QDomNodeList childs = root.childNodes();
	for(int i=0; i<childs.size(); i++)
	{
		QDomElement elem = childs.at(i).toElement();
		QString tagname = elem.tagName();
		if(tagname == "define-parameter") lparams << elem;
		else if(tagname == "define-basic-event") levents << elem;
		else if(tagname == "define-fault-tree") ltree << elem;
	}
	
	for(QDomElement& e : lparams)
		readDistrib(e);
	for(QDomElement& e : levents)
		readEvent(e);
	for(QDomElement& e : ltree)
		readTree(e);

	//association des transfert avec les Trees de même nom
	for(Transfert* transfert : transtreeMap.keys())
	{
		for(Tree &t : e->getTrees())
		{
			if(t.getProperties().getName() == transtreeMap[transfert]) 
			{
				transfert->setLink(&t);
				break;
			}
		}
		if(!transfert->getLink()) throw -1;
	}
}

void XmlTreeReader::readTree(QDomElement &elem)
{
	QList<QDomNodeList> lgates;
	QString name, type, topevt;
	bool keep = false;
	
	name = elem.attribute("name").trimmed();
	if(!e->isUnique(name)) throw -1;

	QDomNodeList attrs = elem.namedItem("attributes").childNodes();

	for(int i=0; i < attrs.size(); i++)
	{
		QDomElement attr = attrs.at(i).toElement();
		if(attr.tagName() != "attribute") throw -1;
		QString attrname = attr.attribute("name").trimmed();
		if(attrname.isEmpty()) throw -1;
		if(attrname == "keep") keep = attr.attribute("value").trimmed() == "true";
		if(attrname == "top-event") topevt = attr.attribute("value").trimmed();
	}
	
	
	e->getTrees() << Tree(name);
	Tree &t = e->getTrees().last();
	t.getProperties().setDesc(elem.namedItem("label").toElement().text().trimmed());
	t.getProperties().setKeep(keep);

	//visit des gate pour les créer
	QDomElement elmgate = elem.namedItem("define-gate").toElement();
	unsigned nbgates = 0;
	while(!elmgate.isNull())
	{
		Gate* g = readGateParams(elmgate, lgates);
		if(g->getProperties().getName() == topevt)
		{
			t.setTop(g);
		}
		nbgates++;
		e->getGates() <<  g; // ajout de la porte à l'éditeur
		elmgate = elmgate.nextSiblingElement("define-gate");
	}
/*
	for(int j=0; j<lgates.size();j++)
	{
		QDomNodeList nl = lgates[j];
		qDebug() << e->getGates()[j]->getProperties().getName()<< "----------";
		for(int i=0; i<lgates.size(); i++)
		{
			qDebug() << nl.at(i).toElement().attribute("name");
		}
	}
*/
	//visit pour les lier à leur fils
	
	for(int i=0; i < lgates.size(); i++)
	{
		readGateChilds(e->getGates()[nodelistcursor+i], lgates.at(i));
	}
	
	nodelistcursor += nbgates;
	/*
	qDebug() << "name: "<< t.getProperties().getName();
	qDebug() << "desc: "<< t.getProperties().getDesc();
	qDebug() << "keep: "<< t.getProperties().getKeep();
	if(t.getTop())
		qDebug() << "Top: " << t.getTop()->getProperties().getName();
	*/
}

void XmlTreeReader::readDistrib(QDomElement &elem)
{
	Distribution *d = nullptr;
	QString name, type;
	bool keep = false;
	
	name = elem.attribute("name").trimmed();
	if(!e->isUnique(name)) throw -1;

	QDomNodeList attrs = elem.namedItem("attributes").childNodes();

	for(int i=0; i < attrs.size(); i++)
	{
		QDomElement attr = attrs.at(i).toElement();
		if(attr.tagName() != "attribute") throw -1;
		QString attrname = attr.attribute("name").trimmed();
		if(attrname.isEmpty()) throw -1;
		
		if(attrname == "keep") keep = attr.attribute("value").trimmed() == "true";
		else if(attrname == "type") type = attr.attribute("value").trimmed();
	}
	
	if(type == "const") d = new Constant(name);
	else if(type == "exp") d = new Exponential(name);
	else if(type == "weibull") d = new Weibull(name);
	else throw -1;

	d->getProperties().setDesc(elem.namedItem("label").toElement().text().trimmed());
	d->getProperties().setKeep(keep);
	
	QDomElement valelem = elem.firstChildElement("float");
	d->setValue(valelem.attribute("value").toDouble());
	if(type == "weibull")
		(dynamic_cast<Weibull*>(d))->setShape(valelem.nextSiblingElement("float").attribute("value").toDouble());
	
	e->getDistributions() << d;
	/*
	qDebug() << "name: "<< d->getProperties().getName();
	qDebug() << "desc: "<< d->getProperties().getDesc();
	qDebug() << "keep: "<< d->getProperties().getKeep();
	qDebug() << "val: "<< d->getValue();
	if(Weibull* w = dynamic_cast<Weibull*>(d))
		qDebug() << "val2: "<< w->getShape();
	*/
}

void XmlTreeReader::readGateChilds(Gate *g, QDomNodeList list)
{
	bool ok = false;
	for(int j=0; j<list.size(); j++)
	{
		QDomElement elem = list.at(j).toElement();
		QString name = elem.attribute("name").trimmed();
		
		if(elem.tagName() == "basic-event")
		{
			for(Event evt : e->getEvents())
			{
				if(evt.getProperties().getName() == name) 
				{
					ok = true;
					//qDebug() << evt.getProperties().getName();
					g->getChildren() << new Container(&evt);
					break;
				}
			}
		}
		else if(elem.tagName() == "gate")
		{
			for(Gate* gg : e->getGates())
			{
				if(gg->getProperties().getName() == name) 
				{
					ok = true;
					//qDebug() << gg->getProperties().getName();
					g->getChildren() << gg;
					break;
				}
			}
		}
		else if(elem.tagName() == "transfert")
		{
			//PB: Transfert cherche Tree pas encore chargé
			//SOLVED: QMap<Transfert*, QString> dans Reader puis recherche parmis les Trees
			ok = true;
			Transfert* transfert = new Transfert();
			//qDebug()<<"Transf";
			g->getChildren() << transfert;
			transtreeMap.insert(transfert, name);
			break;
		}
		if(ok == false) {throw -1;}
		ok = false;
		
	}
}

Gate* XmlTreeReader::readGateParams(QDomElement &elem, QList<QDomNodeList>& lelems)
{
	Gate* g = nullptr;
	bool keep = false, cond = false;
	unsigned k = 0;
	QString type;
	
	QString name = elem.attribute("name").trimmed();
	if(!e->isUnique(name)) throw -1;
	
	QDomNodeList attrs = elem.namedItem("attributes").childNodes();

	for(int i=0; i < attrs.size(); i++)
	{
		QDomElement attr = attrs.at(i).toElement();
		if(attr.tagName() != "attribute") throw -1;
		QString attrname = attr.attribute("name").trimmed();
		if(attrname.isEmpty()) throw -1;
		if(attrname == "keep") keep = attr.attribute("value").trimmed() == "true";
	}
	
	//get Gate Type
	QDomNodeList subelem = elem.childNodes();
	for(int i=0; i<subelem.size(); i++)
	{
		QString type = subelem.at(i).nodeName();
		if(type == "and")
		{
			if(!subelem.at(i).namedItem("constant").isNull())
				{g = new Inhibit(name); ((Inhibit*)g)->setCondition(cond);}
			else g = new And(name);
		}
		else if(type == "or") g = new Or(name);
		else if(type == "xor") g = new Xor(name);
		else if(type == "atleast"){ g = new VotingOR(name); ((VotingOR*)g)->setK(k);}
		
		if(g) {lelems << subelem.at(i).childNodes(); break;}
	}

	if(!g) throw -1;
	g->getProperties().setKeep(keep);
	g->getProperties().setDesc(elem.namedItem("label").toElement().text().trimmed());
	
	return g;
}

void XmlTreeReader::readEvent(QDomElement &elem)
{
	bool keep = false;

	QString name = elem.attribute("name").trimmed();
	if(!e->isUnique(name)) throw -1;

	QDomNodeList attrs = elem.namedItem("attributes").childNodes();

	for(int i=0; i < attrs.size(); i++)
	{
		QDomElement attr = attrs.at(i).toElement();
		if(attr.tagName() != "attribute") throw -1;
		QString attrname = attr.attribute("name").trimmed();
		if(attrname.isEmpty()) throw -1;
		if(attrname == "keep") keep = attr.attribute("value").trimmed() == "true";
	}
	
	QList<Distribution*> ldistribs = e->getDistributions();
	int idst = searchDistribution(ldistribs, elem.namedItem("parameter").toElement().attribute("name").trimmed());

	if(idst == -1) throw -1;

	QList<Event>& levents = e->getEvents();
	levents << Event(name);
	levents.last().getProperties().setKeep(keep);
	levents.last().getProperties().setDesc(elem.namedItem("label").toElement().text().trimmed());
	levents.last().setDistribution(ldistribs[idst]);
	
	/*
	qDebug() << "name: "<< levents.last().getProperties().getName();
	qDebug() << "desc: "<< levents.last().getProperties().getDesc();
	qDebug() << "keep: "<< levents.last().getProperties().getKeep();
	if(levents.last().getDistribution() != nullptr)
		qDebug() << "distrib: "<< levents.last().getDistribution()->getProperties().getName();
	*/
}

int XmlTreeReader::searchDistribution(QList<Distribution*>& distribs, QString name)
{
	for(int i = 0; i < distribs.size(); i++)
	{
		if(distribs[i]->getProperties().getName() == name)
			return i;
	}
	return -1;
}
