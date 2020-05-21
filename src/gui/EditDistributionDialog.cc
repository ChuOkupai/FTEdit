#include "EditDistributionDialog.hh"
#include "WidgetLinker.hh"

// VisitorEditDistribution

VisitorEditDistribution::VisitorEditDistribution(QWidget *parent, Editor &editor) :
parent(parent), editor(editor)
{}

void VisitorEditDistribution::visit(Constant &distribution)
{
	EditConstantDialog(parent, editor, distribution).exec();
}

void VisitorEditDistribution::visit(Exponential &distribution)
{
	EditExponentialDialog(parent, editor, distribution).exec();
}

void VisitorEditDistribution::visit(Weibull &distribution)
{
	EditWeibullDialog(parent, editor, distribution).exec();
}

// EditConstantDialog

EditConstantDialog::EditConstantDialog(QWidget *parent, Editor &editor, Constant &dist) :
PropertiesDialog(parent, editor, &dist.getProperties()), editor(editor), dist(dist)
{
	setWindowTitle("Edit Constant Distribution");
	resize(360, 400);
	WidgetLinker linker(this, (QBoxLayout*)layout());
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	linker.addLabel("Unavailability:");
	value = linker.addDoubleSpinBox();
	value->setRange(0.0, 1.0); // Probability range between 0.0 and 1.0
	value->setDecimals(16); // Precision
	value->setSingleStep(0.01);
	value->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
	value->setValue(dist.getValue());
	value->setButtonSymbols(QAbstractSpinBox::NoButtons); // Disable adjust button
	linker.addOKButton();

	connect(value, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	[=](double d){ this->dist.setValue(d); });
}

// EditExponentialDialog

EditExponentialDialog::EditExponentialDialog(QWidget *parent, Editor &editor, Exponential &dist) :
PropertiesDialog(parent, editor, &dist.getProperties()), editor(editor), dist(dist)
{
	setWindowTitle("Edit Exponential Distribution");
	resize(380, 400);
	WidgetLinker linker(this, (QBoxLayout*)layout());
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	linker.addLabel("Lambda:");
	lambda = linker.addDoubleSpinBox();
	lambda->setRange(0.0, 1.0);
	lambda->setDecimals(16);
	lambda->setSingleStep(0.01);
	lambda->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
	lambda->setValue(dist.getValue());
	lambda->setButtonSymbols(QAbstractSpinBox::NoButtons);
	linker.addOKButton();

	connect(lambda, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	[=](double d){ this->dist.setValue(d); });
}

// TODO

// EditWeibullDialog

EditWeibullDialog::EditWeibullDialog(QWidget *parent, Editor &editor, Weibull &dist) :
PropertiesDialog(parent, editor, &dist.getProperties()), editor(editor), dist(dist)
{
	setWindowTitle("Edit Weibull Distribution");
	resize(360, 400);
	WidgetLinker linker(this, (QBoxLayout*)layout());
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	linker.addLabel("Scale:");
	scale = linker.addDoubleSpinBox();
	scale->setRange(0.0, 1.0);
	scale->setDecimals(16);
	scale->setSingleStep(0.01);
	scale->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
	scale->setValue(dist.getScale());
	scale->setButtonSymbols(QAbstractSpinBox::NoButtons);

	linker.addLabel("Shape:");
	shape = linker.addDoubleSpinBox();
	shape->setRange(0.0, 1.0);
	shape->setDecimals(16);
	shape->setSingleStep(0.01);
	shape->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
	shape->setValue(dist.getShape());
	shape->setButtonSymbols(QAbstractSpinBox::NoButtons);

	linker.addOKButton();

	connect(scale, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	[=](double d){ this->dist.setScale(d); });
	connect(shape, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	[=](double d){ this->dist.setShape(d); });
}


// TODO
