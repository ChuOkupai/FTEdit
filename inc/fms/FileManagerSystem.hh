#pragma once

#include <QString>
#include <QMap>
#include "FTEdit_Editor.hh"
#include "FTEdit_Evaluator.hh"
#include "XmlTreeReader.hh"

class FileManagerSystem
{
	private:
		QMap<Tree*, Gate*> treegatemap;
		QString path;
		QString errorMessage;
	public:
		FileManagerSystem();
		~FileManagerSystem();

		QString getErrorMessage();
		QString getPath();
		int exportAs(QString path, Result &result);
		Editor* load(QString path);
		int save(Editor* editor);
		int saveAs(QString path, Editor* editor);
		void setPath(QString path);
};
