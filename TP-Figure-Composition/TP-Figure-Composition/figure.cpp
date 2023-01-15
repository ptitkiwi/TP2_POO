#include "stdafx.h"
#include "figure.h"
#include "algorithm"
#include "graphSgt.h"
#include "rct.h"

const unsigned long MAX_UL=numeric_limits<unsigned long>::max();
const double MAX_DOUBLE = numeric_limits<double>::max();
class tSgtStack;

// Teste si la figure est dans un état valide
// Le nombre de segments doit etre inférieur ou égal a la taille du tableau
// Tous les segments sont inclus dans le cadre rLmit de la figure
bool figure::valid(void) const
{
	assert(rLimit.valid());
	assert(nDimTS >= 0);
	assert(nSgt >= 0 && nSgt <= nDimTS);
	assert(penWidth > 0);
	assert(nSgt <= nDimTS);
	for (unsigned int i = 0; i < nSgt; i++) 
	{
		assert(rLimit.contains(operator[](i).getCurrentGeo()));
	}
	return true;
}

// constructeurs, destructeur
figure::figure(rct _rLimit)
	:rLimit(_rLimit)
	, pTS(nullptr)
	, nDimTS(0)
	, nSgt(0)
	, penWidth(1)
	, tUpdate(0)
{
	assert(_rLimit.valid());

	assert(valid());
}

figure::~figure(void)
{
	assert(valid());
	delete[] pTS;
}

//Le constructeur de copie par défaut ne convient pas car il copie l'adresse du pointeur ==> On modifie l'original
figure::figure(const figure& f):
	rLimit(f.rLimit),
	nDimTS(f.nDimTS),
	nSgt(f.nSgt),
	penWidth(f.penWidth),
	tUpdate(f.tUpdate)
{
	assert(f.valid());
	pTS = new graphSgt[nDimTS];
	for (unsigned int i = 0; i < nDimTS; i++) {
		pTS[i] = f[i];
	}
	assert(valid());
}

bool figure::operator==(const figure& f) const
{
	assert(valid());
	assert(f.valid());

	if (
		rLimit == f.rLimit
		&& nSgt == f.nSgt
		)
	{
		for (unsigned int i = 0; i < nSgt; i++)
		{
			if (count(operator[](i)) != f.count(operator[](i)))
				return false;
		}
		return true;
	}
	return false;
}


// Insertion dans un flux
ostream& operator<<(ostream& s, const figure& f)
{
	assert(f.valid());

	f.print(s);
	return s;
}

// Renvoie le segment de rang "i", en lecture ou en écriture
graphSgt& figure::operator[](unsigned long i) const
{
	return(pTS[i]);
}

// Ajoute un segment graphique à la figure. La géométrie du segment est donnée
// par l'argument, son épaisseur de trait est l'épaisseur de trait courante de
// la figure et son état est non-sélectionné. Le segement n'est inséré dans la 
// figure que s'il est inclus dans son rectange limite
// Valeur de retour : le rang du nouveau segment dans le tableau de segments.
const unsigned long figure::add(const tSgt s)
{
    assert( valid() );
	if (rLimit.contains(s.getSeg()) == false) {//Verify that the segment is inside the figure, if not, assign max and exit
		return(MAX_UL);
	}
	else {
		if (nSgt >= nDimTS) {  //Check that there is still some space in the segment array
			expand(); //If no place left, expand the array
		}
		tUpdate++;
		pTS[nSgt] = graphSgt(s,penWidth); //Add the segment to the array 
		nSgt++; //Increase the number of segment

		assert(valid());
		return (nSgt - 1);
	}
}

// Renvoie le nombre de segments actuellement sélectionnés
const unsigned long figure::getNbrSelected(void) const
{
    assert(valid());
	
	// On parcout le tableau pour compter le nombre de segment selectrionnés
	unsigned long NbrSelected = 0;
	for (unsigned int i = 0; i < nSgt; i++) {//On suppose que tous les segments sont au début du tableau (pas de "case" vide au milieu)
		if (pTS[i].getSelected() == true) {
			NbrSelected++;
		}
	} 

	return NbrSelected; // On renvoit le nombre de segment selectionnés
}

// Supprime tous les segments sélectionnés et renvoie leur nombre
const unsigned long figure::remove(void)
{
	assert( valid() );
	unsigned long nSgtDeleted = 0;
	bool allSelRemoved = false; //Bool true quand tous les élements séléctionnés ont été supprimés
	while (allSelRemoved == false) {
		allSelRemoved = true;
		for (unsigned int i = 0; i < nSgt;i++) {
			if (pTS[i].getSelected()) {//Si le segment est séléctionné
				pTS[i] = pTS[nSgt-1]; //On déplace le dernier segment à la place de celui que l'on supprime
				nSgt--; //On réduit de 1 la taille du tableau
				nSgtDeleted++;
				allSelRemoved = false; //On demande une nouvelle itération de l'algo
			}
		}
	}
	assert( valid() ); //On vérifie que le nouveau tableau est toujours valide
	return nSgtDeleted; // On retourne le nombre de segments supprimés
}

// Retourne le rang du (ou d'un) segment de la figure qui est le plus proche
// du point argument. Si la figure est vide, déclenche une assertion.
const unsigned long figure::closerTo(pt pRef) const
{
    assert( valid() );

	assert(nSgt > 0);
	double current_min = MAX_DOUBLE;
	unsigned long index_min = 0;
	for (unsigned int i = 0; i < nSgt; i++) {
		if (pTS[i].getCurrentGeo().closerTo(pRef).euclide(pRef) < current_min) {//On teste la distance au point le plus proche
			current_min = pTS[i].getCurrentGeo().closerTo(pRef).euclide(pRef);
			index_min = i;
		}
	}
	
	return (index_min); 
}

// Compte le nombre d'occurrences dans la figure du segment graphique argt
// L'état de sélection n'est pas pris en compte
unsigned long figure::count(const graphSgt& s0) const
{
	unsigned long nb_occur = 0;

	for (unsigned int i = 0; i < nSgt; i++)
		if (operator[](i) == s0 && operator[](i).getCurrentTime() > 0)
			nb_occur++;
	return nb_occur;
}

// Ecrit la figure dans le flux argument : le rectangle cadre et la liste de
// tous les segments datés, un par ligne ; un * précède les segments sélectionnés.
/*
Figure @ 0x012FF74C, epoque : 5
rLimit : RCT[-66.34, -39.59]x[-49.91, 15.22]
[ 0] w( 0) { 1 }SGT(( -65.09, 7.12 ), ( -57.90, -1.40 ))@1
[ 1] w( 2) { 1 }SGT(( -61.36, 4.60 ), ( -63.68, -2.17 ))@2
[ 2] w( 3) { 1 }SGT(( -42.33, -18.81 ), ( -48.41, 5.35 ))@3
[ 3] * w( 4) { 1 }SGT(( -53.13, -6.43 ), ( -45.43, -13.27 ))@4
[ 4] w( 5) { 1 }SGT(( -54.03, 9.37 ), ( -64.17, -10.37 ))@5
5 segment(s) / selection de 1
*/
void figure::print(ostream& s) const
{
	assert( valid() );

	s << "Figure @ " << this << ", epoque : " << tUpdate << endl;
	s << "rLimit :" << rLimit << endl;

	for (unsigned int i = 0; i < nSgt; i++ ) {
		s << "[ " << i << "]	" << pTS[i];
	}
	s << getSize() << " segment(s), " << getNbrSelected() << " selectionne(s)" << endl;
}


// Agrandit le tableau de segments de 10%, mais au moins 8 palces de plus
void figure::expand(void)
{
	assert( valid() );

	unsigned long old_nDimTS = nDimTS; //On sauvegarde l'ancienne taille du tableau
	(floor(0.1 * nDimTS) > 8) ? nDimTS = (unsigned long)(1.1 * nDimTS) : nDimTS+=8; //on prends le max entre +10% et +8
	graphSgt* expanded_pTS = new graphSgt[nDimTS]; //On crée un nouveau tableau 10% + grand
	for (unsigned int i = 0; i < old_nDimTS; i++) {//On assigne l'ancien tableau au nouveau
		expanded_pTS[i] = pTS[i];
	}
	delete(pTS);
	pTS = expanded_pTS;

	assert( valid() );
}