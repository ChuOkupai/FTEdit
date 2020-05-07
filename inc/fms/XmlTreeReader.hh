#pragma once

#include <QXmlStreamReader>
#include "FTEdit.hh"

class XmlTreeReader
{
	private:
		QXmlStreamReader reader;
	public:
		XmlTreeReader(QFile* file);
		~XmlTreeReader();
		void readTree();
		void readDistrib();
		void readEvent();
		void readGate();
};
