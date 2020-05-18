#include <QFile>
#include <QSaveFile>
#include <QTextStream>
#include "FileManagerSystem.hh"
#include "SaveVisitor.hh"
#include <QDebug>

FileManagerSystem::FileManagerSystem() {}

FileManagerSystem::~FileManagerSystem() {}

QString FileManagerSystem::getErrorMessage() { return errorMessage; }

QString FileManagerSystem::getPath() { return path; }

Editor* FileManagerSystem::load(QString path)
{
	errorMessage = "";
	setPath(path);
	QFile file(path);
	if(!file.open(QIODevice::ReadOnly)){
		errorMessage = file.errorString();
		return nullptr;
	}
	
	Editor* editor = new Editor(false);
	XmlTreeReader xtr(&file, editor);

	try { xtr.read();}
	catch(int exp)
	{
		delete editor;
		errorMessage = file.errorString();
		qDebug() << errorMessage;
	}
	/*
	for(Gate* g : editor->getGates())
		qDebug() << g->getProperties().getName() << ": " << g->getChildren().size();
	*/
	file.close();
	editor->setAutoRefresh(true);
	return editor;
}

void gateTreeMapping(Tree* tree, Gate* top, QMap<Tree*, Gate*>* map)
{
	Gate *g = nullptr;
	map->insertMulti(tree, top);
	QList<Node*>& childs = top->getChildren();
	for(Node* c : childs)
		if((g = dynamic_cast<Gate*>(c)) != nullptr)
			gateTreeMapping(tree, g, map);
}

int FileManagerSystem::save(Editor* editor)
{
	errorMessage = "";
	QSaveFile file(path); SaveVisitor svisitor;
	
	if(!file.open(QIODevice::WriteOnly))
	{
		errorMessage = file.errorString();
		qDebug() << errorMessage;
		return -1;
	}
	QTextStream saveStream(&file); QDomDocument& domref = svisitor.getDomFile();
	
	//create root node of xml file
	QDomElement root = domref.createElement("opsa-mef");
	root.setAttribute("author", "FTEdit");
	domref.appendChild(root);

	//visit
	for(Distribution *d :  editor->getDistributions())
		d->accept(svisitor);
	for(Event e :  editor->getEvents())
		e.accept(svisitor);
	
	// visit gate
	for(Tree &tree : editor->getTrees())
	{
		gateTreeMapping(&tree , tree.getTop(), &treegatemap);
	}

	QDomElement treeroot, treelabel, treetop;
 
	for(Tree &tree : editor->getTrees())
	{
		Properties &treeprop = tree.getProperties();
		QDomElement treepropelem = domref.createElement("attributes");
		
		treeroot = domref.createElement("define-fault-tree");
		
		svisitor.writeProperties(treeroot, treepropelem, treeprop);
		if(tree.getTop())
		{
			treetop = domref.createElement("attribute");
			treetop.setAttribute("name", "top-event");
			treetop.setAttribute("value", tree.getTop()->getProperties().getName());
			treepropelem.appendChild(treetop);
		}
		treeroot.appendChild(treepropelem);

		svisitor.setTreeElem(treeroot);//set tree root for SaveVisitor

		QList<Gate*> lgates = treegatemap.values(&tree);
		for(Gate* g : lgates)
			g->accept(svisitor); //visit
		root.appendChild(treeroot);
	}

	saveStream << domref.toString(4);
	file.commit();
	return 0;
}

int FileManagerSystem::saveAs(QString path, Editor* editor)
{
	setPath(path); save(editor); return 0;
}

void FileManagerSystem::setPath(QString path) {this->path = path; }

int FileManagerSystem::exportAs(QString path, Result &result)
{
	errorMessage = "";
	QFile file(path);
	if(!file.open(QIODevice::WriteOnly))
	{
		errorMessage = "Failed to open the file in write mode";
		return -1;
	}
	QTextStream saveStream(&file);

	ResultMCS *resmcs =  result.getResultMCS();
	ResultBoolean *resB = result.getResultBoolean();

	if(resmcs)
	{
		saveStream << "Probability,Quantity,Events" << '\n';
		QList<double> proMcs = resmcs->getProbabilities();
		QList<QList<QString>> cs = resmcs->getMCS();
		int m = cs.size();
		
		for(int i=0; i < m; i++)
		{
			saveStream << proMcs[i] <<','<<cs[i].size()<<',';
			for(QList<QString> l : cs)
				saveStream << l[i]<<" ";
			saveStream << '\n';
		}
		
	}

	if(resB)
	{
		if(resmcs) saveStream << "\n\n";

		saveStream << "Time,Failure rate of " << resB->getTopEventName() << '\n';
		QString topEvenet = resB->getTopEventName();
		double mstep = resB->getStep();
		QList<double> proB = resB->getProbabilities();
		
		double ctime = 0;
		for(double r : proB)
		{
			saveStream << ctime << "," << r <<'\n';
			ctime+=mstep;
		}
	}
	file.close();
	return 0;
}
