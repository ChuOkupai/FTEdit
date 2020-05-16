#include "EditVisitor.hh"
#include "EditDistributionDialog.hh"

EditVisitor::EditVisitor(QWidget *parent, Editor &editor, NodeItem *n) :
parent(parent), editor(editor), n(n)
{}

void EditVisitor::visit(And &gate)
{
	EditGateDialog(parent, editor, gate, "And").exec();
}

void EditVisitor::visit(Or &gate)
{
	EditGateDialog(parent, editor, gate, "Or").exec();
}

void EditVisitor::visit(Xor &gate)
{
	EditGateDialog(parent, editor, gate, "Xor").exec();
}

void EditVisitor::visit(VotingOR &gate)
{
	EditVotingORDialog(parent, editor, gate).exec();
}

void EditVisitor::visit(Inhibit &gate)
{
	EditInhibitDialog(parent, editor, gate).exec();
}

void EditVisitor::visit(Transfert &gate)
{
	EditTransfertDialog(parent, editor, gate).exec();
	n->setProperties(gate.getLink() ? &gate.getLink()->getProperties() : nullptr);
}

void EditVisitor::visit(Container &cont)
{
	EditContainerDialog(parent, editor, cont).exec();
	n->setProperties(&cont.getEvent()->getProperties());
	editor.refresh(); // Remove useless events
}

EditGateDialog::EditGateDialog(QWidget *parent, Editor &editor, Gate &gate, QString name) :
PropertiesDialog(parent, editor, &gate.getProperties())
{
	setWindowTitle("Edit " + name + " Gate");
	resize(360, 400);
	WidgetLinker linker(this, (QBoxLayout*)layout());
	linker.addOKButton();
}

EditInhibitDialog::EditInhibitDialog(QWidget *parent, Editor &editor, Inhibit &gate) :
PropertiesDialog(parent, editor, &gate.getProperties()), gate(gate)
{
	setWindowTitle("Edit Inhibit Gate");
	resize(360, 400);
	WidgetLinker linker(this, (QBoxLayout*)layout());
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	linker.addLabel("Condition:");
	condition = linker.addComboBox();
	condition->addItem("false");
	condition->addItem("true");
	condition->setCurrentIndex(gate.getCondition() == true);
	linker.addOKButton();

	connect(condition, QOverload<int>::of(&QComboBox::currentIndexChanged),
	[=](int i) { this->gate.setCondition(i == 1); });
}

EditVotingORDialog::EditVotingORDialog(QWidget *parent, Editor &editor, VotingOR &gate) :
PropertiesDialog(parent, editor, &gate.getProperties()), gate(gate)
{
	setWindowTitle("Edit Voting or Gate");
	resize(360, 400);
	WidgetLinker linker(this, (QBoxLayout*)layout());
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	linker.addLabel("K parameter:");
	k = linker.addSpinBox();
	k->setRange(0, gate.getChildren().size()); // k range between 0 and n children
	k->setValue(gate.getK());
	linker.addOKButton();

	connect(k, SIGNAL(valueChanged(int)), this, SLOT(updateK(int)));
}

void EditVotingORDialog::updateK(int k2)
{
	gate.setK(k2);
}

EditTransfertDialog::EditTransfertDialog(QWidget *parent, Editor &editor, Transfert &gate) :
QDialog(parent), editor(editor), gate(gate)
{
	setWindowIcon(QIcon(":icons/edit.png"));
	setWindowTitle("Edit Transfert In Gate");
	resize(360, 140);
	WidgetLinker linker(this, new QVBoxLayout(this));
	linker.addLabel("Link:");
	trees = linker.addComboBox();
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
	linker.addOKButton();

	QList<Tree> &l = editor.getTrees();
	trees->addItem(""); // Empty link
	for (int i = 0; i < l.size(); ++i)
		trees->addItem(l[i].getProperties().getName());
	Tree *link = gate.getLink();
	trees->setCurrentIndex(link ? trees->findText(link->getProperties().getName()) : 0);
	
	connect(trees, QOverload<int>::of(&QComboBox::currentIndexChanged),
	[=](int i) { this->gate.setLink(i ? &this->editor.getTrees()[i - 1] : nullptr); });
}

EditContainerDialog::EditContainerDialog(QWidget *parent, Editor &editor, Container &cont) :
PropertiesDialog(parent, editor, &cont.getEvent()->getProperties(), false), cont(cont)
{
	setWindowTitle("Edit event");
	resize(320, 380);
	auto layout = new QVBoxLayout(this);
	WidgetLinker linker(this, layout);
	linker.addLabel("Event:");
	events = linker.addComboBox();
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum));
	init();
	linker.addLabel("Distribution:");
	linker.set(new QHBoxLayout());
	distributions = linker.addComboBox();
	distributions->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	edit = linker.addPushButton("Edit");
	edit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	auto add = linker.addPushButton("+");
	add->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	linker.set(layout);
	linker.addOKButton();

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
	if (ChooseDistributionDialog(this, editor).exec() == QDialog::Rejected)
		return ; // cancel
	Distribution *dist = editor.getDistributions().last();
	distributions->addItem(dist->getProperties().getName());
	distributions->setCurrentIndex(distributions->count() - 1);
}