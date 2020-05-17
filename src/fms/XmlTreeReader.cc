#include "XmlTreeReader.hh"

XmlTreeReader::XmlTreeReader(QFile *f, Editor* e) : reader(f), e(e) {}

XmlTreeReader::~XmlTreeReader() {}

void XmlTreeReader::readTree()
{
	QXmlStreamReader::TokenType toktype;
	
	while(!reader.atEnd())
	{
		toktype = reader.readNext();

		if(toktype == QXmlStreamReader::StartElement)
		{
			if(reader.name() == "define-parameter") readDistrib();
			else if(reader.name() == "define-gate") readGate();
			else if(reader.name() == "define-basic-event") readEvent();
		}
	}
}

void XmlTreeReader::readDistrib()
{
	Distribution *d = nullptr;
	QXmlStreamAttributes attrs;
	QString name, desc, tmp;
	bool keep = false;

	name = getName(); //get name
	reader.readNextStartElement();

	desc = getLabel();

	if(reader.name() != "attributes") throw -1; //raise error


	while(reader.readNextStartElement())
	{
		if(reader.name() != "attribute") throw -1; //raise error

		getKeep(&keep);
		if(reader.attributes().value( "", "name").toString().trimmed() == "type") //get type
		{
			tmp = reader.attributes().value( "", "value").toString().trimmed();
			reader.readNextStartElement();
		}
	}

	if(tmp == "const") d = createConstant(name);
	else if(tmp == "exp") d = createExponential(name);
	else if(tmp == "weibull") d = createWeibull(name);
	
	d->getProperties().setDesc(desc);
	d->getProperties().setKeep(keep);

	e->getDistributions() << d; //ajouter la Distrib à l'éditeur
}

Constant* XmlTreeReader::createConstant(QString name)
{
	reader.readNextStartElement();
	if(reader.name() != "float") throw -1;
	Constant* d = new Constant(name);
	d->setValue(reader.attributes().value( "", "value").toString().toDouble());
	reader.readNextStartElement();
	return d;
}

Exponential* XmlTreeReader::createExponential(QString name)
{
	reader.readNextStartElement();
	if(reader.name() != "float") throw -1;
	Exponential* d = new Exponential(name);
	d->setValue(reader.attributes().value( "", "value").toString().toDouble());
	reader.readNextStartElement();
	return d;
}

Weibull* XmlTreeReader::createWeibull(QString name)
{
	Weibull* d = new Weibull(name);
	reader.readNextStartElement();
	if(reader.name() != "float") { delete d; throw -1; }
	d->setValue(reader.attributes().value( "", "value").toString().toDouble());
	reader.readNextStartElement();
	reader.readNextStartElement();
	if(reader.name() != "float") { delete d; throw -1; }
	d->setShape(reader.attributes().value( "", "value").toString().toDouble());
	reader.readNextStartElement();
	return d;
}

int XmlTreeReader::searchEvent(QList<Event>& events, QString name)
{
	for(int i = 0; i < events.size(); i++)
	{
		if(events[i].getProperties().getName() == name)
			return i;
	}
	return -1;
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

void XmlTreeReader::readGate()
{
	Gate* g = nullptr;
	int ievt = -1, k = 0;
	QList<Node*> childs;
	bool cond = false;

	QXmlStreamAttributes attrs;
	QString name, desc, type, tmp;
	bool keep = false;

	name = getName(); //get name

	reader.readNextStartElement();
	desc = getLabel();

	if(reader.name() != "attributes") throw -1; //raise error
	reader.readNextStartElement();
	if(reader.name() != "attribute") throw -1; //raise error

	getKeep(&keep);

	reader.readNextStartElement();
	reader.readNextStartElement();
	type = reader.name().toString();

	k = reader.attributes().value( "", "min").toUInt(); //..get k
	QList<Event>& levents = e->getEvents();
	while(reader.readNextStartElement())
	{
		if(reader.name() == "basic-event")
		{
			ievt = searchEvent(levents, reader.attributes().value( "", "name").toString().trimmed());
			if(ievt == -1) throw -1;
			childs << new Container(&levents[ievt]);
		}
		else if(reader.name() == "constant")
		{
			type = "inhibit";
			cond = (tmp == "true" ? true : false);
		}
		reader.readNextStartElement();
	}
	
	if(type == "inhibit" && levents.size() > 1) throw -1;

	if(type == "inhibit") { g = new Inhibit(name,true); ((Inhibit*)g)->setCondition(cond);}
	else if(type == "and") g = new And(name,true);
	else if(type == "or") g = new Or(name,true);
	else if(type == "xor") g = new Xor(name,true);
	else if(type == "atleast"){ g = new VotingOR(name,true); ((VotingOR*)g)->setK(k);}
	else throw -1;
	e->getGates() <<  g; // ajout de la porte à l'éditeur
	g->getProperties().setKeep(keep);
	g->getProperties().setDesc(desc);
	g->getChildren() = childs;
}

void XmlTreeReader::readEvent()
{
	bool keep;
	QString name = getName(); //get name
	reader.readNextStartElement();
	QString desc = getLabel(); //get label
	
	if(reader.name() != "attributes") throw -1; //raise error
	reader.readNextStartElement();
	if(reader.name() != "attribute") throw -1; //raise error

	getKeep(&keep); //get keep
	reader.readNextStartElement();
	reader.readNextStartElement();
	
	if(reader.name() != "parameter") throw -1; //get paramaeter

	QList<Distribution*> ldistribs = e->getDistributions();
	int idst = searchDistribution(ldistribs, reader.attributes().value( "", "name").toString().trimmed());

	if(idst == -1) throw -1;

	QList<Event>& levents = e->getEvents();
	levents << Event(name);
	levents.last().getProperties().setKeep(keep);
	levents.last().getProperties().setDesc(desc);
	levents.last().setDistribution(ldistribs[idst]);
}

QString XmlTreeReader::getName()
{
	QString name = reader.attributes().value( "", "name").toString().trimmed(); //get name
	if(!e->isUnique(name)) throw -1;
	return name;
}

QString XmlTreeReader::getLabel()
{
	QString desc = "";
	if(reader.name() == "label")
	{
		desc = reader.readElementText().trimmed(); //get label
		reader.readNextStartElement();
	}
	return desc;
}

void XmlTreeReader::getKeep(bool *b)
{
	QString tmp;
	if(reader.attributes().value( "", "name").toString().trimmed() == "keep") //get keep
	{
		tmp = reader.attributes().value( "", "value").toString().trimmed();
		reader.readNextStartElement();
		*b = (tmp == "true" ? true : false);
	}
}
