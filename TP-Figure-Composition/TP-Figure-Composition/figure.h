#pragma once
#include "rct.h"
#include "graphSgt.h"
class sgt;
class graphSgt;

//******************************************************************************
//
//                       NE PAS MODIFIER CE FICHIER
//                 sauf pour coder l'affectation et la copie
//
//******************************************************************************

class figure
{
private:
    // L'affectation est inaccessible ou bloquée en attendant qu'elle soit cor-
    // rectement codée
	//figure& operator=(const figure&);

public:
// constructeurs, destructeurs, affectation, égalité ____________________________

    // Le constructeur par défaut initialise une figure vide: elle ne dispose pas
    // encore d'un tableau en mémoire dynamique pour stocker les segments, et son
    // rectangle limite est défini par l'argument.
	explicit figure(rct rFig);    // Le mot clé "explicit" interdit la conversion
								  // automatique de rectangle en figure, par exem-
								  // ple dans une fonction qui attend un argument 
	                              // de type figure, mais est appelée avec un argt 
								  // de type rct.

    // Le destructeur libère le tableau des segments graphiques
    ~figure(void);

    // Le constructeur de copie par défaut
	figure(const figure& f);

    // Renvoie "vrai" si et seulement si tous les éléments termes à termes sont égaux
    bool operator==(const figure& f) const;


// Accesseurs ___________________________________________________________________

    // Renvoie le rectangle cadre de la figure
    const rct getRctLimit(void) const;
    // Renvoie le nbr de segments actuellement dans la figure
    const unsigned long getSize(void) const;
    // Accès au segment de rang "i", en lecture ou en écriture
    graphSgt& operator[](unsigned long i) const;
    // Renvoie la taille courante du crayon
    const unsigned long getPenWidth() const;
    // Définit la taille courante du crayon  et renvoie l'ancienne taille
    const unsigned long setPenWidth(unsigned long width);


// Opérations ___________________________________________________________________

    // Ajoute un segment graphique à la figure. Sa géométrie est donnée par l'ar-
    // gument, son épaisseur de trait est l'épaisseur de trait courante de la fi-
    // gure, et son état est non-sélectionné. 
	// Le segment n'est inséré dans la figure que si il est inclus dans son rec-
	// tangle limite.
    // Valeur de retour : le rang du nouveau segment dans le tableau de segments.
    const unsigned long add(const sgt s);

    // Renvoie le nombre de segments actuellement sélectionnés
    const unsigned long getNbrSelected(void) const;

    // Supprime les segments actuellement sélectionnés et renvoie leur nombre. Le
    // rectangle limite n'est pas modifié (pas ajusté aux segments restants).
    const unsigned long remove(void);

    // Retourne le rang du (ou d'un) segment de la figure qui est le plus proche
    // du point argument. Si la figure est vide, déclenche une assertion.
    const unsigned long closerTo(pt pRef) const;

    // Ecrit la figure dans le flux argument : son adresse, le rectangle cadre et
    // la liste de tous les segments, un par ligne, précédes d'un * pour les seg-
    // ments sélectionnés. Le nbr de segments est écrit à la fin.
    void print(ostream& s) const;


private:
// Implémentation _______________________________________________________________

    const rct rLimit;                            // Rectangle limite de la figure
    graphSgt* pTS;         // Adresse du tableau de segments en mémoire dynamique
    unsigned long nDimTS;                     // Dimension du tableau de segments
    unsigned long nSgt;         // Nombre de segments actuellement dans la figure

    // Outil(s) graphique(s)
    unsigned long penWidth;                // Largeur de trait courante du crayon

    // Agrandit le tableau de segments de 10%, mais au moins de 8 places de plus.
    void expand(void);

public:
	// Teste si la figure est dans un état valide : le tableau de segments existe
	// si il y a au moins un segment ; le nbr de segments est inferieur ou égal à
	// la dimension du tableau ; tous les segments sont inclus dans le rectangle
	// limite de la figure.
	bool valid(void) const;
};

// Insertion dans un flux
ostream& operator<<(ostream& s, const figure& f);


// Renvoie le rectangle cadre de la figure
inline const rct figure::getRctLimit(void) const
{ return rLimit; }

// Renvoie le nombre de segments de la figure
inline const unsigned long figure::getSize(void) const
{ return nSgt; }

// Renvoie ou définit la taille courante du crayon
inline const unsigned long figure::getPenWidth() const
{ return penWidth; }
//
inline const unsigned long figure::setPenWidth(unsigned long width)
{
    unsigned long oldWidth = penWidth;
    penWidth = width;
    return oldWidth;
}
