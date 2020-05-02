#include "Widgets.hh"

GraphicsView::GraphicsView(QWidget *parent) :
QGraphicsView(parent)
{
	setDragMode(QGraphicsView::ScrollHandDrag);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
	qreal factor = event->delta() > 0 ? 1.25 : 0.75;
	scale(factor, factor);
}

LineEditName::LineEditName(QWidget *parent, Editor &editor) :
QLineEdit(parent), editor(editor), isValid(true)
{}

QString LineEditName::check(Properties &prop)
{
	QString s = text().trimmed();
	if (!s.compare(prop.getName()) || (s.size() > 0 && editor.isUnique(s)))
	{
		isValid = true;
		setToolTip("");
		setStyleSheet("");
		prop.setName(s);
	}
	else
	{
		isValid = false;
		setToolTip(s.size() ? "This name already exists" : "This name is invalid");
		setStyleSheet("border: 1px solid red;background-color: #ffe3e3;");
	}
	setText(s);
	return (s);
}

bool LineEditName::valid() const
{
	return (isValid);
}