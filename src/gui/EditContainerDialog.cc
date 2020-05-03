#include "Dialog.hh"
#include "EditContainerDialog.hh"
#include "EditDistributionDialog.hh"

EditContainerDialog::EditContainerDialog(QWidget *parent, Editor &editor, Container &cont) :
PropertiesDialog(parent, editor, &cont.getEvent()->getProperties(), false), cont(cont)
{
	setWindowTitle("Edit event");
	resize(360, 480);
	auto layout = new QVBoxLayout(this);
	WidgetLinker linker(this, layout);
	linker.addLabel("Event:");
	events = linker.addComboBox();
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	init();
	linker.addLabel("Distribution:");
	linker.set(new QHBoxLayout());
	distributions = linker.addComboBox();
	distributions->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	edit = linker.addPushButton("Edit");
	edit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	auto add = linker.addPushButton("+");
	add->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

	QList<Distribution*> &l = editor.getDistributions();
	distributions->addItem(""); // Empty distribution
	for (int i = 0; i < l.size(); ++i)
		distributions->addItem(l[i]->getProperties().getName());

	QList<Event> &l2 = editor.getEvents();
	for (int i = 0; i < l2.size(); ++i)
		events->addItem(l2[i].getProperties().getName());

	connect(this, SIGNAL(nameChanged(QString)), this, SLOT(updateName(QString)));
	connect(events, QOverload<int>::of(&QComboBox::currentIndexChanged),
	[=](int index) { this->setEvent(index); });
	connect(distributions, QOverload<int>::of(&QComboBox::currentIndexChanged),
	[=](int index) { this->setDistribution(index); });
	connect(edit, SIGNAL(released()), this, SLOT(editDistribution()));
	connect(add, SIGNAL(released()), this, SLOT(addDistribution()));
	setEvent(events->findText(cont.getEvent()->getProperties().getName()));
}

void EditContainerDialog::updateName(QString s)
{
	events->setItemText(index, (valid() ? s : "* " + s));
}

void EditContainerDialog::setEvent(int index)
{
	if (valid())
	{
		this->index = index;
		cont.setEvent(&editor.getEvents()[index]);
		setProperties(&cont.getEvent()->getProperties());
		events->setCurrentIndex(index);
		Distribution *dist = cont.getEvent()->getDistribution();
		index = dist ? distributions->findText(dist->getProperties().getName()) : 0;
		distributions->blockSignals(true);
		distributions->setCurrentIndex(index);
		distributions->blockSignals(false);
		edit->setEnabled(index); // enabled if index > 0
	}
	else
		events->setCurrentIndex(this->index);
}

void EditContainerDialog::setDistribution(int index)
{
	distributions->setCurrentIndex(index);
	edit->setEnabled(index); // enabled if index > 0
	if (!index)
	{
		cont.getEvent()->setDistribution(nullptr);
		return ;
	}
	Distribution *dist = editor.getDistributions()[index - 1];
	cont.getEvent()->setDistribution(dist);
}

void EditContainerDialog::editDistribution()
{
	Distribution *dist = cont.getEvent()->getDistribution();
	VisitorEditDistribution v(this, editor);
	dist->accept(v);
	distributions->setItemText(distributions->currentIndex(), dist->getProperties().getName());
}

void EditContainerDialog::addDistribution()
{
	ChooseDistributionDialog(this, editor).exec();
	Distribution *dist = editor.getDistributions().last();
	distributions->addItem(dist->getProperties().getName());
	distributions->setCurrentIndex(distributions->count() - 1);
}