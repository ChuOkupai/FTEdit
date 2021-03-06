#pragma once
#include <QtWidgets>

class DoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT

private:
	QString textFromValue(double d) const;

public:
	DoubleSpinBox(QWidget *parent = nullptr);
	static QString toStringNotFilled(double d, char f = 'g', int prec = 6);
};

class WidgetLinker
{
private:
	QWidget *parent;
	QBoxLayout *layout;

public:
	WidgetLinker(QWidget *parent, QBoxLayout *layout);
	~WidgetLinker();

	QCheckBox *addCheckBox(const QString &content);

	QComboBox *addComboBox();

	DoubleSpinBox *addDoubleSpinBox();

	QLabel *addLabel(const QString &content);

	QLayoutItem *addLayoutItem(QLayoutItem *item);

	QLineEdit *addLineEdit(const QString &content);

	// Add an OK button and link its signal to closeEvent() if link is set to true
	QPushButton *addOKButton(bool link = true);

	QPushButton *addPushButton(const QString &content);

	QRadioButton *addRadioButton(const QString &content);

	QSpinBox *addSpinBox();

	QTabWidget *addTabWidget();

	QTableWidget *addTableWidget();

	QTextEdit *addTextEdit(const QString &content);

	// Sets the parent widget
	void set(QWidget *parent);
	// Sets a layout make a link with the previous one
	void set(QBoxLayout *layout);
	// Use another layout
	void replace(QBoxLayout *layout, QBoxLayout *with);
};

// Custom button for toolbar

class GateToolButton : public QToolButton
{
	Q_OBJECT

public:
	GateToolButton(QWidget *parent);
};

// Custom QListView
class ListWidget : public QListWidget
{
	Q_OBJECT

private slots:
	void contextMenuEvent(QContextMenuEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	QAction *removeOne;

public:
	ListWidget(QWidget *parent);
};

#define ZOOM_MIN	0.042
#define ZOOM_MAX	2.5
#define ZOOM_STEP	0.4
#define ZOOM_SCROLL	0.15

// Custom QGraphicsView widget for smooth edition
class GraphicsView : public QGraphicsView
{
	Q_OBJECT

protected Q_SLOTS:
	void wheelEvent(QWheelEvent *event);

public:
	GraphicsView(QWidget *parent);

	// Set a new zoom factor
	void setZoom(qreal factor);
	// Get the current zoom factor
	qreal zoom();
};