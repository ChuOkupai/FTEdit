#pragma once
#include <QtWidgets>

/*
** Classe qui sert d'interface temporaire pour simplifier la création des
** éléments disposés sur la fenêtre.
*/

class WidgetLinker
{
private:
    QWidget *parent;
    QBoxLayout *layout;

public:
    WidgetLinker(QWidget *parent, QBoxLayout *layout);
    ~WidgetLinker();

    QComboBox *addComboBox();

    QLabel *addLabel(const QString &content);

    QLayoutItem *addLayoutItem(QLayoutItem *item);

    QPushButton *addPushButton(const QString &content);

    QLineEdit *addLineEdit(const QString &content);

    QTextEdit *addTextEdit(const QString &content);

    // Sets the parent widget
    void set(QWidget *parent);
    // Sets a layout make a link with the previous one
    void set(QBoxLayout *layout);
    // Use another layout
    void replace(QBoxLayout *layout, QBoxLayout *with);
};
