#pragma once
#include <QtWidgets>

class WidgetLinker
{
private:
	QWidget *parent;
	QBoxLayout *layout;

public:
	WidgetLinker(QWidget *parent, QBoxLayout *layout);
	~WidgetLinker();

	QComboBox *addComboBox();

	QDoubleSpinBox *addDoubleSpinBox();

	QLabel *addLabel(const QString &content);

	QLayoutItem *addLayoutItem(QLayoutItem *item);

	QLineEdit *addLineEdit(const QString &content);

	// Add an OK button and link its signal to closeEvent()
	QPushButton *addOKButton();

	QPushButton *addPushButton(const QString &content);

	QRadioButton *addRadioButton(const QString &content);

	QTextEdit *addTextEdit(const QString &content);

	// Sets the parent widget
	void set(QWidget *parent);
	// Sets a layout make a link with the previous one
	void set(QBoxLayout *layout);
	// Use another layout
	void replace(QBoxLayout *layout, QBoxLayout *with);
};

// Custom QGraphicsView widget for smooth edition

class GraphicsView : public QGraphicsView
{
	Q_OBJECT

protected Q_SLOTS:
	// Zoom view (rescale)
	void wheelEvent(QWheelEvent *event);

public:
	GraphicsView(QWidget *parent);
};