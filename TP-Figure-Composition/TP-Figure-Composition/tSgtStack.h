#pragma once
#include "tSgt.h"

class tSgtStack
{
public :
	
	// Constructeurs, Destructeurs, Opérateurs

	tSgtStack(void);				// Constructeur par défaut

	tSgtStack(const tSgtStack& _t);	// Constructeur par copie

	~tSgtStack(void);				// Le destructeur libère le tableau des segments graphiques

	// Renvoie "vrai" si et seulement si tous les éléments termes à termes sont égaux
	bool operator==(const tSgtStack& t) const;

	//Opérateur d'affectation
	void operator=(const tSgtStack& t);


	// Accesseurs

	// Renvoie le nbr de segments actuellement dans la Stack
	const unsigned long getSize(void) const;


	// Opérations

	// Empilement d'un segment daté
	const unsigned long push(const tSgt tseg);

	// Accède au segment daté en tête de pile
	tSgt top(void) const;

	// Supprime l'élément en tête de pile 
	void pop(void);

	// Ecriture dans un flux de la pile
	void print(ostream& s) const;

	// Teste si la pile est dans un état valide :
	bool valid(void) const;

private :

	tSgt* ptSgt;					// Adresse de la pile de segments datés en mémoire dynamique
	unsigned long nDimStack;	// Dimension de la pile de segments datés
	unsigned long ntSgt;		// Nombre de segments datés actuellement dans la pile

	// Agrandit la pile de 10%, mais au moins de 8 cases de plus.
	void expand(void);
};

// Fonctions Inline

inline const unsigned long tSgtStack::getSize(void) const
{
	return(ntSgt);
};