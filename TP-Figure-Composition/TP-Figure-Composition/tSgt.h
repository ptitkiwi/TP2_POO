#pragma once
#include "sgt.h"

class graphSgt;

class tSgt
{
private :
	sgt seg;
	double date;

public :

	// Constructeurs

	tSgt(void);			// Constructeur par défaut
	tSgt(sgt _seg, double _date);	// Constructeur par surcharge	

	// Renvoie "vrai" si et seulement si tous les éléments termes à termes sont égaux
	bool operator==(const tSgt& s) const;

	// Accesseurs

	const sgt getSeg(void) const;	// Getter segment
	const double getDate(void) const;	// Getter date

	// Ecriture dans un flux au format : SGT(( pt1.X, pt1.Y ), ( pt2.X, pt2.Y ))@date
	void print(ostream& s) const;
};


// Insertion dans un flux
ostream& operator<<(ostream& s, const tSgt& f);

// Fonctions Inline

inline const sgt tSgt::getSeg(void) const
{
	return(seg);
};

inline const double tSgt::getDate(void) const
{
	return(date);
};