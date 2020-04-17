#include "Properties.hh"

namespace std;

Properties::Properties(QString name) : name(name)
{
	QString desc;
	refCount = 1;
	keep = true;
}
Properties::~Properties()
{

}

QString const Properties::getName(){return name;}
QString const Properties::getDesc(){return desc;}
bool const Properties::getKeep(){return keep;}

void Properties::setName(QString name) : name(name){}
void Properties::setDesc(QString desc) : desc(desc){}
void Properties::setKeep(bool keep) : keep(keep){}

void Properties::decrementRefCount()
{
	refCount = refCount - 1;
}
void Properties::incrementRefCount()
{
	refCount = refCount + 1;
}
bool Properties::canBeRemoved()
{
	if (kepp == false && refCount == 0)
	{
		return true;
	}else{
		return false;
	}
}
