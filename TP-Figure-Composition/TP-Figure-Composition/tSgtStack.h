#pragma once
#include "tSgt.h"

class tSgtStack
{
private:

	tSgt* ptSgt;					// Adresse de la pile de segments dat�s en m�moire dynamique
	unsigned long nDimStack;	// Dimension de la pile de segments dat�s
	unsigned long ntSgt;		// Nombre de segments dat�s actuellement dans la pile

	// Agrandit la pile de 10%, mais au moins de 8 cases de plus.
	void expand(void);

public :
	
	// Constructeurs, Destructeurs, Op�rateurs

	tSgtStack();				// Constructeur par d�faut

	tSgtStack(const tSgtStack& _t);	// Constructeur par copie

	//~tSgtStack(void);				// Le destructeur lib�re le tableau des segments graphiques

	// Renvoie "vrai" si et seulement si tous les �l�ments termes � termes sont �gaux
	bool operator==(const tSgtStack& t) const;

	//Op�rateur d'affectation
	void operator=(const tSgtStack& t);

	// Acc�s au segment de rang "i", en lecture ou en �criture
	tSgt& operator[](unsigned long i) const;

	// Accesseurs

	// Renvoie le nbr de segments actuellement dans la Stack
	const unsigned long getSize(void) const;


	// Op�rations

	// Empilement d'un segment dat�
	const void push(const tSgt tseg);

	// Acc�de au segment dat� en t�te de pile
	const tSgt top(void) const;

	// Supprime l'�l�ment en t�te de pile 
	void pop(void);

	// Ecriture dans un flux de la pile
	void print(ostream& s) const;

	// Teste si la pile est dans un �tat valide :
	bool valid(void) const;
};

// Insertion dans un flux
ostream& operator<<(ostream& s, const tSgtStack& f);

// Fonctions Inline

inline const unsigned long tSgtStack::getSize(void) const
{
	return(ntSgt);
};