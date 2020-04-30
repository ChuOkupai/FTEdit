#include <QtGlobal>
#include <QDebug>
#include "Editor.hh"
#include "EditContainerDialog.hh"
#include "WidgetLinker.hh"

void EditContainerDialog::closeEvent(QCloseEvent *event)
{
	checkName();
	if (valid)
	{
		cont.getEvent()->getProperties().setDesc(desc->toPlainText());
		event->accept();
	}
	else
		event->ignore();
}

void EditContainerDialog::checkName()
{
	QString s = name->text().trimmed();
	if (!s.compare(cont.getEvent()->getProperties().getName()) || (s.size() > 0 && editor.isUnique(s)))
	{
		valid = true;
		name->setToolTip("");
		name->setStyleSheet(styleSheet());
		cont.getEvent()->getProperties().setName(s);
	}
	else
	{
		valid = false;
		name->setToolTip(s.size() ? "This name is invalid" : "This name already exists");
		name->setStyleSheet("border: 1px solid red;background-color: #ffe3e3;");
	}
	events->setItemText(index, s);
	name->setText(s);
}

void EditContainerDialog::setEvent(int index)
{
	if (valid)
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
	}
	else
		events->setCurrentIndex(this->index);
}

void EditContainerDialog::setDistribution(int index)
{
	distributions->setCurrentIndex(index);
	if (!index)
	{
		//cont.getEvent()->setDistribution(nullptr); (segfault)
		return ;
	}
	Distribution *dist = editor.getDistributions()[index - 1];
	cont.getEvent()->setDistribution(dist);
}

void EditContainerDialog::editDistribution()
{
	if (!distributions->currentIndex())
		return ;
	Distribution *dist = cont.getEvent()->getDistribution();
	// EditDistributionDialog(this, editor, dist);
	distributions->setItemText(distributions->currentIndex(), dist->getProperties().getName());
}

void EditContainerDialog::addDistribution()
{
	QList<Distribution*> &l = editor.getDistributions();
	// Ajouter pop-up pour choisir le type de distribution
	auto *dist = new Constant(editor.generateName("Model"));
	l << dist;
	distributions->addItem(dist->getProperties().getName());
	distributions->setCurrentIndex(distributions->count() - 1);
}

EditContainerDialog::EditContainerDialog(QWidget *parent, Editor &editor, Container &cont)
: QDialog(parent), editor(editor), cont(cont), valid(true)
{
	this->setWindowTitle("Edit event");
	this->resize(360, 480);
	auto layout = new QVBoxLayout(this);
	WidgetLinker linker(this, layout);
	linker.addLabel("Event");
	events = linker.addComboBox();
	linker.addLayoutItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum));
	linker.addLabel("Name");
	name = linker.addLineEdit("");
	linker.addLabel("Description");
	desc = linker.addTextEdit(cont.getEvent()->getProperties().getDesc());
	linker.addLabel("Distribution");
	linker.set(new QHBoxLayout());
	distributions = linker.addComboBox();
	distributions->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	auto edit = linker.addPushButton("Edit");
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