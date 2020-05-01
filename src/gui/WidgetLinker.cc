#include "WidgetLinker.hh"

WidgetLinker::WidgetLinker(QWidget *parent, QBoxLayout *layout) :
parent(parent), layout(layout)
{}

WidgetLinker::~WidgetLinker() {}

QComboBox *WidgetLinker::addComboBox()
{
	auto *comboBox = new QComboBox(parent);
	layout->addWidget(comboBox);
	return (comboBox);
}

QLabel *WidgetLinker::addLabel(const QString &content)
{
	auto *label = new QLabel(parent);
	label->setText(content);
	layout->addWidget(label);
	return (label);
}

QLayoutItem *WidgetLinker::addLayoutItem(QLayoutItem *item)
{
	layout->addItem(item);
	return (item);
}

QLineEdit *WidgetLinker::addLineEdit(const QString &content)
{
	auto *lineEdit = new QLineEdit(parent);
	lineEdit->setText(content);
	layout->addWidget(lineEdit);
	return (lineEdit);
}

QPushButton *WidgetLinker::addPushButton(const QString &content)
{
	auto *button = new QPushButton(parent);
	button->setText(content);
	layout->addWidget(button);
	return (button);
}

QRadioButton *WidgetLinker::addRadioButton(const QString &content)
{
	auto *button = new QRadioButton(parent);
	button->setText(content);
	layout->addWidget(button);
	return (button);
}

QTextEdit *WidgetLinker::addTextEdit(const QString &content)
{
	auto *textEdit = new QTextEdit(parent);
	textEdit->setText(content);
	layout->addWidget(textEdit);
	return (textEdit);
}

void WidgetLinker::set(QWidget *parent)
{
	this->parent = parent;
}

void WidgetLinker::set(QBoxLayout *layout)
{
	if (!layout->parent())
		this->layout->addLayout(layout);
	this->layout = layout;
}

void WidgetLinker::replace(QBoxLayout *layout, QBoxLayout *with)
{
	with->addLayout(layout);
	this->layout = layout;
}
