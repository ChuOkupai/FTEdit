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
    //(void)distribution;
    EditExponentialDialog(parent, editor, distribution).exec();
}

void VisitorEditDistribution::visit(Weibull &distribution)
{
    //(void)distribution;
    EditWeibullDialog(parent, editor, distribution).exec();
}

// EditConstantDialog

EditConstantDialog::EditConstantDialog(QWidget *parent, Editor &editor, Constant &dist) :
PropertiesDialog(parent, editor, &dist.getProperties()), editor(editor), dist(dist)
{
    setWindowTitle("Edit Constant Distribution");
	WidgetLinker linker(this, (QBoxLayout*)layout());
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	linker.addLabel("Unavailability:");
	value = linker.addDoubleSpinBox();
	value->setRange(0.0, 1.0); // Probability range between 0.0 and 1.0
	value->setDecimals(16); // Precision
	value->setSingleStep(0); // Disable step
	value->setValue(dist.getValue());
	value->setButtonSymbols(QAbstractSpinBox::NoButtons); // Disable adjuste button
	linker.addOKButton();

	connect(value, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
	[=](double d){ this->dist.setValue(d); });
}

// EditExponentialDialog

EditExponentialDialog::EditExponentialDialog(QWidget *parent, Editor &editor, Exponential &dist) :
PropertiesDialog(parent, editor, &dist.getProperties()), editor(editor), dist(dist)
{
    setWindowTitle("Edit Exponential Distribution");
    WidgetLinker linker(this, (QBoxLayout*)layout());
    linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
    linker.addLabel("Unavailability:");
    value = linker.addDoubleSpinBox();
    value->setRange(0.0, 1.0); // Probability range between 0.0 and 1.0
    value->setDecimals(16); // Precision
    value->setSingleStep(0); // Disable step
    value->setValue(dist.getValue());
    value->setButtonSymbols(QAbstractSpinBox::NoButtons);

    linker.addLabel("Lambda:");
    lambda = linker.addDoubleSpinBox();
    lambda->setSingleStep(0);
    lambda->setValue(dist.getLambda());
    lambda->setButtonSymbols(QAbstractSpinBox::NoButtons);

    linker.addOKButton();

    connect(value, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
    [=](double d){ this->dist.setValue(d); });
}

// TODO

// EditWeibullDialog

EditWeibullDialog::EditWeibullDialog(QWidget *parent, Editor &editor, Weibull &dist) :
PropertiesDialog(parent, editor, &dist.getProperties()), editor(editor), dist(dist)
{
    setWindowTitle("Edit Weibull Distribution");
    WidgetLinker linker(this, (QBoxLayout*)layout());
    linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
    linker.addLabel("Unavailability:");
    value = linker.addDoubleSpinBox();
    value->setRange(0.0, 1.0); // Probability range between 0.0 and 1.0
    value->setDecimals(16); // Precision
    value->setSingleStep(0); // Disable step
    value->setValue(dist.getValue());
    value->setButtonSymbols(QAbstractSpinBox::NoButtons);

    linker.addLabel("Scale:");
    scale = linker.addDoubleSpinBox();
    scale->setSingleStep(0);
    scale->setValue(dist.getScale());
    scale->setButtonSymbols(QAbstractSpinBox::NoButtons);

    linker.addLabel("Shape:");
    shape = linker.addDoubleSpinBox();
    shape->setSingleStep(0);
    shape->setValue(dist.getShape());
    shape->setButtonSymbols(QAbstractSpinBox::NoButtons);

    linker.addOKButton();

    connect(value, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
    [=](double d){ this->dist.setValue(d); });
}


// TODO
