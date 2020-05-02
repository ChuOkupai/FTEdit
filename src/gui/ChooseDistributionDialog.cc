#include "ChooseDistributionDialog.hh"
#include "WidgetLinker.hh"

void ChooseDistributionDialog::closeEvent(QCloseEvent *event)
{
	QString name = editor.generateName("Model");
	if (laws->checkedId() == 1)
		*dist = new Constant(name);
	else if (laws->checkedId() == 2)
		*dist = new Exponential(name);
	else
		*dist = new Weibull(name);
	event->accept();
}

void ChooseDistributionDialog::confirm()
{
	this->close();
}

ChooseDistributionDialog::ChooseDistributionDialog(QWidget *parent, Editor &editor, Distribution **dist)
: QDialog(parent), editor(editor), dist(dist)
{
	setWindowTitle("New model");
	resize(300, 200);
	auto layout = new QVBoxLayout(this);
	WidgetLinker linker(this, layout);
	linker.addLayoutItem(new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
	auto hLayout = new QHBoxLayout();
	linker.set(hLayout);
	linker.addLayoutItem(new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
	linker.set(new QVBoxLayout());
	linker.addLabel("Law of probability:");
	laws = new QButtonGroup(this);
	auto button = linker.addRadioButton("Constant");
	button->setChecked(true);
	laws->addButton(button, 1);
	laws->addButton(linker.addRadioButton("Exponential"), 2);
	laws->addButton(linker.addRadioButton("Weibull"), 3);
	linker.set(hLayout);
	linker.addLayoutItem(new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
	linker.set(layout);
	linker.addLayoutItem(new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
	linker.replace(new QHBoxLayout(), layout);
	linker.addLayoutItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	auto ok = linker.addPushButton("OK");
	ok->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

	connect(ok, SIGNAL(released()), this, SLOT(confirm()));
}