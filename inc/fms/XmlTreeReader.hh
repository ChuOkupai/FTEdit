#pragma once

#include <QXmlStreamReader>
#include "FTEdit.hh"

class XmlTreeReader
{
	private:
		QXmlStreamReader reader;
		Editor* e;
		bool error;
		Constant* createConstant(QString name);
		Exponential* createExponential(QString name);
		Weibull* createWeibull(QString name);
		int searchEvent(QList<Event>& events, QString name);
		QString getName();
		QString getLabel();
		bool getKeep();
	public:
		XmlTreeReader(QFile* file, Editor* e);
		~XmlTreeReader();
		void readTree();
		void readDistrib();
		void readEvent();
		void readGate();
};
