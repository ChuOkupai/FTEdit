#pragma once
#include "Distribution.hh"
#include "Event.hh"
#include "Gate.hh"
#include "Tree.hh"

#define PREFIX_DISTRIBUTION	"Distribution"
#define PREFIX_EVENT		"Event"
#define PREFIX_GATE			"Gate"
#define PREFIX_TRANSFERT	"Transfert"
#define PREFIX_TREE			"Tree"

class Node;

class Editor
{
private:
	QList<Tree>				trees;
	QList<Event>			events;
	QList<Distribution*>	distributions;
	QList<Gate*>			gates;
	Node					*clipboard;
	Tree					*selection;
	bool					autoRefresh;

public:
	Editor(bool autoRefresh = true);
	~Editor();

	QList<Tree>				&getTrees();
	QList<Event>			&getEvents();
	QList<Distribution*>	&getDistributions();
	QList<Gate*>			&getGates();
	Node					*getClipboard();
	Tree					*getSelection();

	void	setSelection(Tree *selection);
	void	setAutoRefresh(bool value = true);

	//Retire les noms en doublons des Gates et Tree en partant de top (créé pour paste) 
	void 	remove_duplicate_names(Node* top);
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
	// Détache un sous-arbre si il existe et le déplace dans un nouvel arbre
	void	detach(Gate *top = nullptr);
	// Fusionne le contenu d'un arbre dans un autre
	void	join(Tree *child, Gate *parent);
	// Génère un nom non utilisé pour un objet
	QString	generateName(QString prefix);
	// Vérifie si name est déjà utilisé dans un objet de l'éditeur
	bool	isUnique(QString name);
	// Mise à jour des listes d'objets de l'éditeur (détruit les objets non utilisés)
	void	refresh();
	// Réinitialise le presse-papier
	void	resetClipboard();
};