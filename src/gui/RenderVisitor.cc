#include "EditVisitor.hh"

NodeItem::NodeItem(Editor &editor, QPixmap icon, Node *n, Properties *prop, bool isChild) :
QGraphicsRectItem(n->getPosition().x(), n->getPosition().y(), CARD_X, CARD_Y),
editor(editor), icon(icon), n(n), prop(prop), child(isChild)
{
	pressed = false;
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
}

bool NodeItem::isChild()
{
	return (child);
}

Node *NodeItem::node()
{
	return (n);
}

void NodeItem::setProperties(Properties *prop)
{
	this->prop = prop;
	update();
}

QRectF NodeItem::boundingRect() const
{
	return QRectF(n->getPosition().x(), n->getPosition().y(), CARD_X, CARD_Y);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	(void)option;
	(void)widget;
	QRectF r = boundingRect();
	r.setHeight(r.height() - ICON_RSIZE);
	QPen pen(Qt::black, BORDER_SIZE);
	painter->setPen(pen);
	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addRoundedRect(r, ICON_RSIZE / 2, ICON_RSIZE / 2);
	path.addRect(r.x(), r.y() + r.height() / 4 - BORDER_SIZE / 2, r.width(), 0);
	painter->setPen(pen);
	painter->fillPath(path, (isSelected() ? QColor(213, 236, 255) : Qt::white));
	painter->drawPath(path);
	QPointF p(r.x() + ICON_RSIZE, r.y() + 1.89 * ICON_RSIZE + BORDER_SIZE - 1);
	painter->drawPixmap(p, icon);
	if (prop)
	{
		QFont font = painter->font();
		font.setPixelSize(ICON_RSIZE / 4);
		painter->setFont(font);
		QRect r2(r.x() + ICON_RSIZE / 4, r.y() + ICON_RSIZE / 8,
		r.width() - ICON_RSIZE / 2, r.height() / 4 - BORDER_SIZE);
		painter->drawText(r2, Qt::AlignLeft, prop->getName());
		r2.setY(r.y() + r.height() / 4);
		r2.setHeight(r.height() - r.height() / 4 - BORDER_SIZE);
		painter->drawText(r2, Qt::TextWordWrap, prop->getDesc());
	}
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	pressed = true;
	update();
	QGraphicsItem::mousePressEvent(event);
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	pressed = false;
	if (event->button() == Qt::LeftButton)
		setSelected(true);
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}

void NodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	setSelected(true);
	QMenu menu;
	menu.addAction("Edit");
	QAction *a = menu.exec(event->screenPos());
	if (!a) return ; // No action selected
	if (a->text() == "Edit")
	{
		EditVisitor visitor((QWidget*)parentWidget(), editor, this);
		n->accept(visitor);
		scene()->update();
	}
}

RenderVisitor::RenderVisitor(QGraphicsScene *scene, Editor &editor, Node *selection) :
scene(scene), editor(editor), selection(selection)
{
	(void)this->view;
	scene->clear();
	if (editor.getSelection()->getTop())
		editor.getSelection()->getTop()->accept(*this);
}

// Visits the children of gate recursively
static void visitChildren(Gate &gate, RenderVisitor &visitor)
{
	QList<Node*> &children = gate.getChildren();
	QList<Node*>::const_iterator i;
	for (i = children.constBegin(); i != children.constEnd(); ++i)
		(*i)->accept(visitor);
}

void RenderVisitor::visit(And &gate)
{
	visitChildren(gate, *this);
	static QPixmap icon(QPixmap(":objects/and.png").scaled(ICON_RSIZE, ICON_RSIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	auto n = new NodeItem(editor, icon, &gate, &gate.getProperties());
	if (&gate == selection) n->setSelected(true);
	scene->addItem(n);
}

void RenderVisitor::visit(Or &gate)
{
	visitChildren(gate, *this);
	static QPixmap icon(QPixmap(":objects/or.png").scaled(ICON_RSIZE, ICON_RSIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	auto n = new NodeItem(editor, icon, &gate, &gate.getProperties());
	if (&gate == selection) n->setSelected(true);
	scene->addItem(n);
}

void RenderVisitor::visit(Xor &gate)
{
	visitChildren(gate, *this);
	static QPixmap icon(QPixmap(":objects/xor.png").scaled(ICON_RSIZE, ICON_RSIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	auto n = new NodeItem(editor, icon, &gate, &gate.getProperties());
	if (&gate == selection) n->setSelected(true);
	scene->addItem(n);
}

void RenderVisitor::visit(VotingOR &gate)
{
	visitChildren(gate, *this);
	static QPixmap icon(QPixmap(":objects/kn.png").scaled(ICON_RSIZE, ICON_RSIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	auto n = new NodeItem(editor, icon, &gate, &gate.getProperties());
	if (&gate == selection) n->setSelected(true);
	scene->addItem(n);
}

void RenderVisitor::visit(Inhibit &gate)
{
	visitChildren(gate, *this);
	static QPixmap icon(QPixmap(":objects/inhibit.png").scaled(ICON_RSIZE, ICON_RSIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	auto n = new NodeItem(editor, icon, &gate, &gate.getProperties());
	if (&gate == selection) n->setSelected(true);
	scene->addItem(n);
}

void RenderVisitor::visit(Transfert &gate)
{
	Properties *prop = gate.getLink() ? &gate.getLink()->getProperties() : nullptr;
	static QPixmap icon(QPixmap(":objects/transfert.png").scaled(ICON_RSIZE, ICON_RSIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	auto n = new NodeItem(editor, icon, &gate, prop, true);
	if (&gate == selection) n->setSelected(true);
	scene->addItem(n);
}

void RenderVisitor::visit(Container &cont)
{
	static QPixmap icon(QPixmap(":objects/basicEvent.png").scaled(ICON_RSIZE, ICON_RSIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	auto n = new NodeItem(editor, icon, &cont, &cont.getEvent()->getProperties(), true);
	if (&cont == selection) n->setSelected(true);
	scene->addItem(n);
}