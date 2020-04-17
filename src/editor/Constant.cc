#include "Constant.hh"

Constant::Constant(QString name) : Distribution(name) {}

double Constant::getProbability(double time) { (void)time; return value; }
