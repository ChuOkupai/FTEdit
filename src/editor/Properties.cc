#include <QDebug>
#include "Properties.hh"

Properties::Properties(QString name, bool keep) :
name(name), refCount(0), keep(keep)
{}

Properties::Properties(const Properties& cop) : name(cop.getName()) , refCount(cop.refCount) , keep(cop.getKeep())
{}
Properties::~Properties()
{}

QString Properties::getName() const
{
	return (name);
}

QString Properties::getDesc() const
{
	return (desc);
}

bool Properties::getKeep() const
{
	return (keep);
}

void Properties::setName(QString name)
{
	this->name = name;
}

void Properties::setDesc(QString desc)
{
	this->desc = desc;
}

void Properties::setKeep(bool keep)
{
	this->keep = keep;
}

void Properties::decrementRefCount()
{
	--refCount;
}

void Properties::incrementRefCount()
{
	++refCount;
}

bool Properties::canBeRemoved()
{
	return (!keep && !refCount);
}
