#include <QFile>
#include <QSaveFile>
#include <QTextStream>
#include "FileManagerSystem.hh"
#include "SaveVisitor.hh"

FileManagerSystem::FileManagerSystem() {}

FileManagerSystem::~FileManagerSystem() {}

QString FileManagerSystem::getErrorMessage() { return errorMessage; }

QString FileManagerSystem::getPath() { return path; }

Editor* FileManagerSystem::load(QString path)
{ 
	this->path = path;
	QFile svfile(path);
	if(!svfile.open(QIODevice::ReadOnly)){
		errorMessage = "Cannot read file" + svfile.errorString();
		qDebug() << errorMessage;
		return nullptr;
	}
	
	Editor* editor = new Editor();
	XmlTreeReader xtr(&svfile);
	xtr.readTree();
	
	return editor;
}

int FileManagerSystem::save(Editor* editor)
{
	QSaveFile file(path); SaveVisitor svisitor;
	
	if(!file.open(QIODevice::WriteOnly))
	{
		errorMessage = "Failed to open the file in write mode";
		return -1;
	}
	QTextStream saveStream(&file); QDomDocument& domref = svisitor.getDomFile();
	
	//create root node of xml file
	QDomElement root = domref.createElement("open-psa");
	root.setAttribute("author", "FTEdit");
	domref.appendChild(root);

	//visit
	
	for(Distribution *d :  editor->getDistributions())
		d->accept(svisitor);
	/*for(Event e :  editor->getEvents())
		e.accept(svisitor);
	*/for(Gate* g :  editor->getGates())
		g->accept(svisitor);

	saveStream << domref.toString();
	file.commit();
	return 0;
}

int FileManagerSystem::saveAs(QString path, Editor* editor)
{
	setPath(path); save(editor); return 0;
}

void FileManagerSystem::setPath(QString path) {this->path = path; }
