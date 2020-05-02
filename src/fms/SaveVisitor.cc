#include "SaveVisitor.hh"

SaveVisitor::SaveVisitor() {}

SaveVisitor::~SaveVisitor() {}

QDomDocument SaveVisitor::getDomFile() { return dom; }

void SaveVisitor::visit( And &andgate ) { (void)andgate; }

void SaveVisitor::visit( Or &orgate ) { (void)orgate;}

void SaveVisitor::visit( Xor &xorgate ) {(void)xorgate;}

void SaveVisitor::visit( Inhibit &inhibgate ) {(void)inhibgate;}

void SaveVisitor::visit( Transfert &transfertgate ) {(void)transfertgate;}

void SaveVisitor::visit( Constant &constdistrib ) {(void)constdistrib;}

void SaveVisitor::visit( Exponential &expdistrib ) {(void)expdistrib;}

void SaveVisitor::visit( Weibull &weibulldistrib ) {(void)weibulldistrib;}

void SaveVisitor::visit( Container &container ) {(void)container;}

void SaveVisitor::visit( Event &event ) {(void)event;}
