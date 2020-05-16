#pragma once
#include <QFile>
#include <QXmlStreamReader>
#include "FTEdit_Editor.hh"

class XmlTreeReader
{
	private:
		QXmlStreamReader reader;
		Editor* e;
		Constant* createConstant(QString name);
		Exponential* createExponential(QString name);
		Weibull* createWeibull(QString name);
		int searchEvent(QList<Event>& events, QString name);
		int searchDistribution(QList<Distribution*>& distribs, QString name);
		QString getName();
		QString getLabel();
		void getKeep(bool *b);
	public:
		XmlTreeReader(QFile* file, Editor* e);
		~XmlTreeReader();
		void readTree();
		void readDistrib();
		void readEvent();
		void readGate();
};
