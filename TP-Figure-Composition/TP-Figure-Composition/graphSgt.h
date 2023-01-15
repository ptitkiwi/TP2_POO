#pragma once
#include "sgt.h"
#include "tSgt.h"
#include "tSgtStack.h"


class graphSgt
{
private:
	// Data _________________________________________________________________________

	// Un segment graphique sera défini par un segment, par l'épaisseur de trait du segment et le fait d’être sélectionné ou pas.
	double  width;
	bool isSelected;
	tSgtStack tseg;
public:
	// constructeurs, destructeurs, affectation, égalité ____________________________
	graphSgt(tSgt _tseg, double _width);
	// Construction par défaut : 
	graphSgt(void);
	// Renvoie "vrai" si et seulement si tous les éléments termes à termes sont égaux
	bool operator==(const graphSgt& s) const;
	// Opérateur d'affectation entre Segments datés graphiques
	graphSgt& operator=(const graphSgt& _gs);
	// Accès au segment de rang "i", en lecture ou en écriture
	tSgt& operator[](unsigned long i) const;

	// Accesseurs ___________________________________________________________________
	// 
	// Renvoie le segment daté courant de la géométrie
	const tSgt getSegment(void) const;
	// Renvoie le taille du segment graphique 
	const double getWidth(void) const;
	// Renvoie le(s) segment(s) graphique(s) selectionné(s)
	const bool getSelected(void) const;
	// Renvoie l'état courant de la géométrie
	const sgt getCurrentGeo(void)const;
	// Renvoie la date courante de la géométrie
	const double getCurrentTime(void)const;
	// Renvoie le nombre d'états mémorisés
	const long getStateCount(void)const;

	// Empilement d'un segment daté graphique
	const void push(const tSgt _tseg);
	// Supprime l'élément en tête de pile du segment graphique 
	void pop(void);

	// Assigne une taille de trait à un segment
	void setWidth(double _width);
	// Selectionne un/des segment(s)
	void setSelected(bool _isSelected);

	// Opérations ___________________________________________________________________

	// Teste si la figure est dans un état valide : le tableau de segments existe
	// si il y a au moins un segment ; le nbr de segments est inferieur ou égal à
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
// Renvoie le segment daté courant de la géométrie

inline const tSgt graphSgt::getSegment(void) const
{
	return this->tseg.top();
}

// Renvoie le taille du segment graphique 
inline const double graphSgt::getWidth(void) const {
	return(width);
};
// Renvoie le(s) segment(s) graphique(s) selectionné(s)
inline const bool graphSgt::getSelected(void) const{
	return(isSelected);
}
inline const sgt graphSgt::getCurrentGeo(void) const
{
	tSgt tSeg = this->getSegment();
	sgt seg = tSeg.getSeg();

	return sgt(seg);
}
inline const double graphSgt::getCurrentTime(void) const
{
	tSgt tSeg = this->getSegment();
	return (tSeg.getDate());
}
inline const long graphSgt::getStateCount(void) const
{
	return tseg.getSize();
}
inline void graphSgt::setWidth(double _width)
{
	width = _width;
}
inline void graphSgt::setSelected(bool _isSelected)
{
	isSelected = _isSelected;
}

