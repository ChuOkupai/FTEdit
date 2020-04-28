#include <QFile>
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
	
	QFile file(path); SaveVisitor sv;
	
	if(!file.open(QIODevice::WriteOnly))
	{
		errorMessage = "Failed to open the file in write mode";
		return -1;
	}
	
	//visit  
	return 0;
}

int FileManagerSystem::saveAs(QString path, Editor* editor)
{
	setPath(path); save(editor); return 0;
}

void FileManagerSystem::setPath(QString path) {this->path = path; }
