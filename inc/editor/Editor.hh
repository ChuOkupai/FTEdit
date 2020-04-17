#pragma once
#include "Distribution.hh"
#include "Event.hh"
#include "Gate.hh"
#include "Tree.hh"

class Editor
{
private:
	QList<Tree>			trees;
	QList<Event>		events;
	QList<Distribution>	distributions;
	QList<Gate>			gates;
	Node				*clipboard;
	Tree				*selection;
	bool				autoRefresh;

public:
	Editor(bool autoRefresh);

	QList<Tree>			&getTrees() const;
	QList<Event>		&getEvents() const;
	QList<Distribution>	&getDistributions() const;
	QList<Gate>			&getGates() const;
	Node				*getClipboard() const;
	Tree				*getSelection() const;
	
	void	setSelection(Tree *selection);
	void	setAutoRefresh(bool value);

	// Mise à jour des listes d'objets de l'éditeur
	void	refresh();
	// Vérifie si name est déjà utilisé dans un objet
	bool	isUnique(QString name);
	// Génère un nom non utilisé pour un objet
	QString	generateName(QString prefix);
	// Réinitialise le presse-papier
	void	resetClipboard();
	// Copie la structure d'un sous-arbre
	void	copy(Node *top);
	// Copie la structure d'un sous-arbre avec sa suppression
	void	cut(Node *top);
	// Colle le contenu du presse-papier à l'endroit passé en paramètre
	void	paste(Gate *parent);
	// Déplace un noeud dans le sous-arbre
	void	move(Node *child, Gate *parent);
	// Supprime récursivement un sous-arbre
	void	remove(Node *top);
	// Détache un sous-arbre et le déplace dans un nouvel arbre
	void	detach(Gate *top);
	// Fusionne le contenu d'un arbre dans un autre
	void	join(Tree *child, Gate *parent);
};