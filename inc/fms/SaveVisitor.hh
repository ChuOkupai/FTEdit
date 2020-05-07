#pragma once

#include <QDomDocument>
#include <QString>
#include "FTEdit_Editor.hh"

class SaveVisitor
{
	private :
		QDomDocument dom;
		void writeProperties(QDomElement &elem, Gate& gate);
		void writeChildren(QDomElement &node, Gate& gate);
		void writeGate(Gate& gate, QString type);
	public :
		SaveVisitor();
		~SaveVisitor();
		QDomDocument& getDomFile();
		void visit( And &andgate );
		void visit( Or &orgate );
		void visit( Xor &xorgate );
		void visit( VotingOR &vorgate );
		void visit( Transfert &transfertgate );
		void visit( Inhibit &inhibgate );
		void visit( Constant &constdistrib );
		void visit( Exponential &expdistrib );
		void visit( Weibull &weibulldistrib );
		void visit( Container &container );
		void visit( Event &event );
};
