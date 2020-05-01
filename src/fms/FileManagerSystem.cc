#include <QFile>
#include <QTextStream>
#include "FileManagerSystem.hh"
#include "SaveVisitor.hh"

FileManagerSystem::FileManagerSystem() {}

FileManagerSystem::~FileManagerSystem() {}

QString FileManagerSystem::getErrorMessage() { return errorMessage; }

QString FileManagerSystem::getPath() { return path; }

Editor* FileManagerSystem::load(QString path) { (void)path; return 0; }

int FileManagerSystem::save(Editor* editor)
{
	(void) editor;
	
	QFile file(path); SaveVisitor svisitor;
	
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
	for(Event e :  editor->getEvents())
		e.accept(svisitor);
	for(Gate* g :  editor->getGates())
		g->accept(svisitor);

	saveStream << domref.toString();
	file.close();
	return 0;
}

int FileManagerSystem::saveAs(QString path, Editor* editor)
{
	setPath(path); save(editor); return 0;
}

void FileManagerSystem::setPath(QString path) {this->path = path; }
