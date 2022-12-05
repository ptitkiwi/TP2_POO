//******************************************************************************
//                                                                             *
//                     NE PAS MODIFIER CE FICHIER SAUF                         *
//     pour ajouter des include ou des définitions de fonctions en-lignes      *
//                                                                             *
//******************************************************************************
#pragma once
#include "pt.h"


class sgt
{
	// Data _________________________________________________________________________

	// La première extrémité et la seconde extrémité du segment
	// Les extrémités sont distinguées (comme pour un vecteur)
	pt p1, p2;


public:
	// Construction _________________________________________________________________

	// Construction par défaut : les deux extrémités se trouvent à l'origine
	sgt(void);
	// Constuction à partir de deux points
	sgt(const pt& p1_, const pt& p2_);
	// L'opérateur d'affectation implicite et le constructeur de copie implicite
	// conviennent : on ne les code pas explicitement.

	// Accesseurs ___________________________________________________________________

	// Renvoie une copie du premier point du segt
	const pt get_p1(void) const;

	// Donne une valeur au premier point du segt
	void set_p1(pt p1_);

	// Renvoie une copie du second point du segt
	const pt get_p2(void) const;

	// Donne une valeur au second point du segt
	void set_p2(pt p1_);

	// Fonctions qui retournent les limites des intervalles définis par les pro-
	// jections du segment sur les axes x et y : [x1, x2] et [y1, y2]
	double x1(void) const;
	double x2(void) const;
	double y1(void) const;
	double y2(void) const;

	// Opérations ___________________________________________________________________

	// Renvoie vrai si le segment d'appel et l'argument sont égaux : leurs premières
	// extrémités sont égales et leurs secondes extrémités sont égales.
	bool operator==(const sgt& s2) const;

	// Renvoie la longueur du segment (distance euclidienne entre ses extrémités)
	double length(void) const;

	// Translation du segment de (dx,dy)
	sgt& offset(double dx, double dy);

	// Renvoie le point milieu du segment.
	pt centerPt(void) const;

	// Renvoie un point situé sur le segment qui est le plus proche du point argument
	pt closerTo(pt p) const;

	// Renvoie la distance euclidienne du segment au point argument
	// nom : euclide

	// Modifie la longueur du segment sans changer son point milieu, ni son 
	// orientation. La largeur est modifiée d'un certain % donné en argment.
	// Cet argument peut être compris entre 0 et 1, ce qui correspond à une 
	// réduction de longueur, ou bien supérieur à 1, ce qui correspond à une
	// augmentation de longueur. Mais il ne peut pas être négatif.
	// nom : inflate

	// Renvoie un point aléatoire situé sur le segment
	pt randPt(void) const;

	// Ecriture dans un flux au format : SGT((x,y), (x,y))
	void print(ostream& s) const;
};

// Insertion d'un segment dnas un flux
ostream& operator<<(ostream& f, const sgt& s);




//--------------------------------------------------------------------------
//Fonctions inline

// Accesseurs ___________________________________________________________________
// Renvoie une copie du premier point du segt
inline const pt sgt::get_p1(void) const
{
	return(p1);
}

// Donne une valeur au premier point du segt
inline void sgt::set_p1(pt p1_)
{
	p1 = p1_;
}

// Renvoie une copie du second point du segt
inline const pt sgt::get_p2(void) const
{
	return(p2);
}

// Donne une valeur au second point du segt
inline void sgt::set_p2(pt p2_)
{
	p2 = p2_;
}




// Fonctions qui retournent les limites des intervalles définis par les pro-
// jections du segment sur les axes x et y : [x1, x2] et [y1, y2]
inline double sgt::x1(void) const 
{
	return min(p1.getX(), p2.getX());
}

inline double sgt::x2(void) const
{
	return max(p1.getX(), p2.getX());
}

inline double sgt::y1(void) const
{
	return min(p1.getY(), p2.getY());
}

inline double sgt::y2(void) const
{
	return max(p1.getY(), p2.getY());
}



