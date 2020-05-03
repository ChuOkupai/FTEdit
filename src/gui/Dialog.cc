#include "Dialog.hh"
#include "WidgetLinker.hh"

void ChooseDistributionDialog::closeEvent(QCloseEvent *event)
{
	QString name = editor.generateName("Model");
	Distribution *dist;
	if (laws->checkedId() == 1)
		dist = new Constant(name);
	else if (laws->checkedId() == 2)
		dist = new Exponential(name);
	else
		dist = new Weibull(name);
	editor.getDistributions() << dist; // Append new distribution to list
	event->accept();
}

ChooseDistributionDialog::ChooseDistributionDialog(QWidget *parent, Editor &editor)
: QDialog(parent), editor(editor)
{
	setWindowTitle("New model");
	auto layout = new QVBoxLayout(this);
	WidgetLinker linker(this, layout);
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	auto hLayout = new QHBoxLayout();
	linker.set(hLayout);
	linker.addLayoutItem(new QSpacerItem(60, 0, QSizePolicy::Maximum, QSizePolicy::Minimum));
	linker.set(new QVBoxLayout());
	linker.addLabel("Law of probability:");
	laws = new QButtonGroup(this);
	auto button = linker.addRadioButton("Constant");
	button->setChecked(true);
	laws->addButton(button, 1);
	laws->addButton(linker.addRadioButton("Exponential"), 2);
	laws->addButton(linker.addRadioButton("Weibull"), 3);
	linker.set(hLayout);
	linker.addLayoutItem(new QSpacerItem(60, 0, QSizePolicy::Maximum, QSizePolicy::Minimum));
	linker.set(layout);
	linker.addOKButton();
}

PropertiesDialog::PropertiesDialog(QWidget *parent, Editor &editor, Properties *prop, bool initialized) :
QDialog(parent), prop(prop), isValid(true), editor(editor)
{
	if (!initialized)
		return ;
	init();
}

void PropertiesDialog::closeEvent(QCloseEvent *event)
{
	isValid ? event->accept() : event->ignore();
}

void PropertiesDialog::checkName()
{
	QString s = nameWidget->text().trimmed();
	if (!s.compare(prop->getName()) || (s.size() > 0 && editor.isUnique(s)))
	{
		isValid = true;
		nameWidget->setToolTip("");
		nameWidget->setStyleSheet("");
		prop->setName(s);
	}
	else
	{
		isValid = false;
		nameWidget->setToolTip(s.size() ? "This name already exists" : "This name is invalid");
		nameWidget->setStyleSheet("border: 1px solid red;background-color: #ffe3e3;");
	}
	nameWidget->setText(s);
	emit nameChanged(s); // Signal
}

void PropertiesDialog::editDesc()
{
	prop->setDesc(descWidget->toPlainText());
}

void PropertiesDialog::init()
{
	if (!this->layout())
		new QVBoxLayout(this);
	WidgetLinker linker(this, (QBoxLayout*)this->layout());
	linker.addLabel("Name:");
	nameWidget = linker.addLineEdit(prop->getName());
	linker.addLabel("Description:");
	descWidget = linker.addTextEdit(prop->getDesc());
	connect(nameWidget, SIGNAL(editingFinished()), this, SLOT(checkName()));
	connect(descWidget, SIGNAL(textChanged()), this, SLOT(editDesc()));
}

void PropertiesDialog::setProperties(Properties *prop)
{
	this->prop = prop;
	nameWidget->blockSignals(true);
	nameWidget->setText(prop->getName());
	nameWidget->blockSignals(false);
	descWidget->blockSignals(true);
	descWidget->setText(prop->getDesc());
	descWidget->blockSignals(false);
}

bool PropertiesDialog::valid()
{
	return (isValid);
}