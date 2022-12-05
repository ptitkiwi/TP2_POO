#pragma once
#include "sgt.h"
class sgt;

class graphSgt
{
private:
	// Data _________________________________________________________________________

	// Un segment graphique sera d�fini par un segment, par l'�paisseur de trait du segment et le fait d��tre s�lectionn� ou pas.
	double  width;
	bool isSelected;
	sgt segment;
public:
	// constructeurs, destructeurs, affectation, �galit� ____________________________
	graphSgt(sgt _segment);
	// Construction par d�faut : 
	graphSgt(void);
	// Renvoie "vrai" si et seulement si tous les �l�ments termes � termes sont �gaux
	bool operator==(const graphSgt& s) const;


	// Accesseurs ___________________________________________________________________
	// 
	// Renvoie le segment
	const sgt getSegment(void) const;
	// Renvoie le taille du segment graphique 
	const double getWidth(void) const;
	// Renvoie le(s) segment(s) graphique(s) selectionn�(s)
	const bool getSelected(void) const;

	// Assigne une taille de trait � un segment
	void setSegment(sgt _segment);
	// Assigne une taille de trait � un segment
	void setWidth(double _width);
	// Selectionne un/des segment(s)
	void setSelected(bool _isSelected);

	// Op�rations ___________________________________________________________________

	// Teste si la figure est dans un �tat valide : le tableau de segments existe
	// si il y a au moins un segment ; le nbr de segments est inferieur ou �gal �
	// la dimension du tableau ; tous les segments sont inclus dans le rectangle
	// limite de la figure.
	bool valid(void) const;

	// Ecriture dans un flux au format : * SGT(PT( -1305.71, 6604.08 ), PT( -3372.95, 4475.2 ))[1]
	void print(ostream& s) const;
};

// Insertion dans un flux
ostream& operator<<(ostream& s, const graphSgt& gSgt);

//--------------------------------------------------------------------------
//Fonctions inline

// Accesseurs ___________________________________________________________________
// 
// Renvoie le segment
inline const sgt graphSgt::getSegment(void) const{
	return(segment);
};
// Renvoie le taille du segment graphique 
inline const double graphSgt::getWidth(void) const {
	return(width);
};
// Renvoie le(s) segment(s) graphique(s) selectionn�(s)
inline const bool graphSgt::getSelected(void) const{
	return(isSelected);
}
inline void graphSgt::setSegment(sgt _segment)
{
	segment = _segment;
}
inline void graphSgt::setWidth(double _width)
{
	width = _width;
}
inline void graphSgt::setSelected(bool _isSelected)
{
	isSelected = _isSelected;
}

