#pragma once

#include <QDomDocument>
#include <QMap>
#include "FTEdit_Editor.hh"

class XmlTreeReader
{
	private:
		QDomDocument dom;
		Editor* e;
		unsigned nodelistcursor;
		QMap<Transfert*, QString> transtreeMap;
		int searchDistribution(QList<Distribution*>& distribs, QString name);
		Gate* readGateParams(QDomElement &elem, QList<QDomNodeList>& lelems);
		void readGateChilds(Gate *g, QDomNodeList list);

		/*
		QString getName();
		QString getLabel();
		*/
		
	public:
		XmlTreeReader(QFile* file, Editor* e);
		~XmlTreeReader();
		void read();
		void readTree(QDomElement &elem);
		void readDistrib(QDomElement &elem);
		void readEvent(QDomElement &elem);
};
