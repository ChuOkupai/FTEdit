#include "ChooseDistributionDialog.hh"
#include "EditContainerDialog.hh"
#include "EditDistributionDialog.hh"

void EditContainerDialog::closeEvent(QCloseEvent *event)
{
	checkName();
	if (name->valid())
	{
		cont.getEvent()->getProperties().setDesc(desc->toPlainText());
		event->accept();
	}
	else
		event->ignore();
}

void EditContainerDialog::checkName()
{
	QString s = name->check(cont.getEvent()->getProperties());
	events->setItemText(index, (name->valid() ? s : "* " + s));
}

void EditContainerDialog::setEvent(int index)
{
	if (name->valid())
	{
		this->index = index;
		Properties *p = &cont.getEvent()->getProperties();
		p->setDesc(desc->toPlainText());
		cont.setEvent(&editor.getEvents()[index]);
		p = &cont.getEvent()->getProperties();
		name->setText(p->getName());
		desc->setText(p->getDesc());
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
	EditDistributionDialog(this, dist);
	distributions->setItemText(distributions->currentIndex(), dist->getProperties().getName());
}

void EditContainerDialog::addDistribution()
{
	QList<Distribution*> &l = editor.getDistributions();
	// Ajouter pop-up pour choisir le type de distribution
	Distribution *dist;
	ChooseDistributionDialog(this, editor, &dist).exec();
	l << dist;
	distributions->addItem(dist->getProperties().getName());
	distributions->setCurrentIndex(distributions->count() - 1);
}

EditContainerDialog::EditContainerDialog(QWidget *parent, Editor &editor, Container &cont)
: QDialog(parent), editor(editor), cont(cont)
{
	setWindowTitle("Edit event");
	resize(360, 480);
	auto layout = new QVBoxLayout(this);
	WidgetLinker linker(this, layout);
	linker.addLabel("Event:");
	events = linker.addComboBox();
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	linker.addLabel("Name:");
	name = linker.addLineEditName(editor);
	linker.addLabel("Description:");
	desc = linker.addTextEdit("");
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

	connect(name, SIGNAL(editingFinished()), this, SLOT(checkName()));
	connect(events, QOverload<int>::of(&QComboBox::currentIndexChanged),
	[=](int index) { this->setEvent(index); });
	connect(distributions, QOverload<int>::of(&QComboBox::currentIndexChanged),
	[=](int index) { this->setDistribution(index); });
	connect(edit, SIGNAL(released()), this, SLOT(editDistribution()));
	connect(add, SIGNAL(released()), this, SLOT(addDistribution()));
	setEvent(events->findText(cont.getEvent()->getProperties().getName()));
}