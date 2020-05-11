#include "WidgetLinker.hh"

DoubleSpinBox::DoubleSpinBox(QWidget *parent) :
QDoubleSpinBox(parent)
{}

QString DoubleSpinBox::textFromValue(double val) const
{
	QLocale locale;
	return (locale.toString(val));
}

WidgetLinker::WidgetLinker(QWidget *parent, QBoxLayout *layout) :
parent(parent), layout(layout)
{}

WidgetLinker::~WidgetLinker() {}

QCheckBox *WidgetLinker::addCheckBox(const QString &content)
{
	auto *checkBox = new QCheckBox(content, parent);
	layout->addWidget(checkBox);
	return (checkBox);
}

QComboBox *WidgetLinker::addComboBox()
{
	auto *comboBox = new QComboBox(parent);
	layout->addWidget(comboBox);
	return (comboBox);
}

DoubleSpinBox *WidgetLinker::addDoubleSpinBox()
{
	auto *spinBox = new DoubleSpinBox(parent);
	layout->addWidget(spinBox);
	return (spinBox);
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

QPushButton *WidgetLinker::addOKButton()
{
	layout->addItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum));
	auto hLayout = new QHBoxLayout();
	layout->addLayout(hLayout);
	hLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Maximum));
	auto *button = new QPushButton(parent);
	button->setText("OK");
	hLayout->addWidget(button);
	button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
	parent->connect(button, SIGNAL(released()), parent, SLOT(close()));
	return (button);
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

QSpinBox *WidgetLinker::addSpinBox()
{
	auto *spinBox = new QSpinBox(parent);
	layout->addWidget(spinBox);
	return (spinBox);
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

GateToolButton::GateToolButton(QWidget *parent) :
QToolButton(parent)
{
	setPopupMode(QToolButton::MenuButtonPopup);
	QObject::connect(this, SIGNAL(triggered(QAction*)), this, SLOT(setDefaultAction(QAction*)));
}

GraphicsView::GraphicsView(QWidget *parent) :
QGraphicsView(parent)
{
	setDragMode(QGraphicsView::ScrollHandDrag);
	setMouseTracking(true);
	viewport()->setMouseTracking(true);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
	qreal f = 1;

	if (event->delta() < 0 && (f -= ZOOM_SCROLL) * zoom() < ZOOM_MIN)
		setZoom(ZOOM_MIN);
	else if (event->delta() > 0 && (f += ZOOM_SCROLL) * zoom() > ZOOM_MAX)
		setZoom(ZOOM_MAX);
	else
		scale(f, f);
}

void GraphicsView::setZoom(qreal factor)
{
	scale(0.1, 0.1);
	resetMatrix();
	scale(factor, factor);
}

qreal GraphicsView::zoom()
{
	return transform().m11();
}