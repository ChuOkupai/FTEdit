#include "Distribution.hh"

Distribution::Distribution(QString name) : Properties(name) {}

Properties& Distribution::getProperties() { return prop; }

double Distribution::getValue() { return value; }

void Distribution::setValue(double value) { this->value = value; }


