#include "XmlTreeReader.hh"

XmlTreeReader::XmlTreeReader(QFile *f) : reader(f) {}

XmlTreeReader::~XmlTreeReader() {}

void XmlTreeReader::readTree()
{
	QString s;
	while(!reader.atEnd())
	{
		if(reader.readNext())
		{
			//if(reader.tokenType())
			//{
				s = reader.name().toString().trimmed();
				qDebug() << "name:" << s;
				s = reader.text().toString().trimmed();
				qDebug() << "text:" << s;
			//}
			//s = reader.readElementText().trimmed();
			//qDebug() << "text:" << s;
		}
	}
}

void XmlTreeReader::readDistrib()
{
	
}

void XmlTreeReader::readEvent()
{
	
}

void XmlTreeReader::readGate()
{
	
}
