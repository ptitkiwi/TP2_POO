#include "stdafx.h"
#include "figure.h"
#include "graphSgt.h"
#include "algorithm"

const unsigned long MAX_UL=numeric_limits<unsigned long>::max();
const double MAX_DOUBLE = numeric_limits<double>::max();
class sgt;

// Teste si la figure est dans un état valide
// Le nombre de segments doit etre inférieur ou égal a la taille du tableau
// Tous les segments sont inclus dans le cadre rLmit de la figure
bool figure::valid(void) const
{
	assert(nSgt <= nDimTS);
	for (unsigned int i = 0; i < nSgt; i++) {
		assert(rLimit.contains(pTS[i].getSegment()));
	}
	return true;
}

// constructeurs, destructeur
figure::figure(rct _rLimit)
	:rLimit(_rLimit)
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
	penWidth(f.penWidth)
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
	assert(f.valid());
	assert(valid());
	for (unsigned int i = 0; i < nSgt; i++) {
		if (!(pTS[i] == f[i])) {
			return false;
		}
	}
	return(getSize() == f.getSize() //nSgt
		&& getPenWidth() == f.getPenWidth()
		&& nDimTS == f.nDimTS
		);
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
const unsigned long figure::add(const sgt s)
{
    assert( valid() );
	if (rLimit.contains(s) == false) {//Verify that the segment is inside the figure, if not, assign max and exit
		return(MAX_UL);
	}
	else {
		if (nSgt >= nDimTS) {  //Check that there is still some space in the segment array
			expand(); //If no place left, expand the array
		}
		graphSgt graph_s = graphSgt(s); //Create a new graph segment from a segment
		graph_s.setWidth(penWidth); //Retrieve current pen width
		pTS[nSgt] = graph_s; //Add the segment to the array 
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
		if (pTS[i].getSegment().closerTo(pRef).euclide(pRef) < current_min) {//On teste la distance au point le plus proche
			current_min = pTS[i].getSegment().closerTo(pRef).euclide(pRef);
			index_min = i;
		}
	}
	
	return (index_min); 
}

// Ecrit la figure dans le flux argument : le rectangle cadre et la liste de
// tous les segments, un par ligne ; un * précède les segments sélectionnés.
/*
Figure @ 0x0x7fff5fbff5d8
rLimit : RCT[-4911.11, 3336.31]x[0, 7978.43]
 SGT(PT( 0, 0 ), PT( 0, 0 ))[1]&
* SGT(PT( -1305.71, 6604.08 ), PT( -3372.95, 4475.2 ))[1]
* SGT(PT( 761.883, 7179.23 ), PT( -4596.9, 7469.87 ))[6]
* SGT(PT( 1378.17, 5274.92 ), PT( -339.927, 4622.5 ))[9]
 SGT(PT( -4664.63, 7366.77 ), PT( -2004.75, 6254.84 ))[1]
 SGT(PT( -116.04, 4539.21 ), PT( -3731.75, 4391.97 ))[7]
* SGT(PT( -3910.39, 7978.43 ), PT( 2404.3, 5389.72 ))[8]
 SGT(PT( -2801.39, 7138.51 ), PT( -2160.43, 5948.75 ))[7]
* SGT(PT( 1036.58, 7294.03 ), PT( -2407.38, 5113.87 ))[9]
 SGT(PT( -2366.05, 7869.29 ), PT( 305.288, 6726.83 ))[0]
10 segment(s), 5 sélectionné(s)
*/
void figure::print(ostream& s) const
{
	assert( valid() );

	s << "Figure @ " << this << endl;
	s << "rLimit :" << rLimit<<endl;
	for (unsigned int i = 0; i < nSgt; i++ ) {
		s << pTS[i] << endl;
	}
	s << nSgt << " segment(s), " << getNbrSelected() << " selectionne(s)" << endl;
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