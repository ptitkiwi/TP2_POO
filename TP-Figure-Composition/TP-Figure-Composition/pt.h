#pragma once
#include <iostream>
#include <cassert>
#include <climits>
#include <cmath>
#include <algorithm>
using namespace std;


class pt
{
private:
   // Data
   double x, y;                                          // Coordonnées du point

public:
   // Constructeurs _____________________________________________________________

   pt(void);                                          // Point initialisé à (0,0)
   pt(double x_, double y_);        // Point initialisé aux coordonnées arguments

   // L'opérateur d'affectation implicite et le constructeur de copie implicite
   // conviennent. On ne les code pas explicitement.

   // Accesseurs ________________________________________________________________

   const double getX(void) const;              // Renvoie la valeur de l’abscisse
   const double getY(void) const;              // Renvoie la valeur de l’ordonnée

   void setX(double x_);            // Donne la valeur de l'argument à l'abscisse
   void setY(double y_);            // Donne la valeur de l'argument à l’ordonnée

   // Opérations ________________________________________________________________

   // Translate (déplacement relatif) le point de (dx,dy)
   pt& offset(double dx, double dy);

   // Effectue une rotation de +90° autour de l'origine et se renvoie lui-même
   pt& rotate90(void);

   // Effectue une symétrie par rapport à l'axe Y et se renvoie lui-même
   pt& symY(void);

   // Renvoie "vrai" si et seulement si le point est égal au point argument
   bool operator==(const pt& p2) const;

   //Applique un offset
   void operator+=(const pt& p2);

   //Compare les normes euclidiennes de deux points
   bool operator<(const pt& p2);

   // Renvoie la distance euclidienne entre le point et le point argument
   double euclide(const pt& p2) const;

   // Renvoie le point milieu du segment allant du point au point argument
   pt centerPt(const pt& p2) const;

   // Renvoie la distance du point au segment de droite [p1,p2]. Au retour, si
   // le pointeur pCloserPt est non nul, alors *pCloserPt sera le point du sgt
   // [p1, p2] qui se trouve le plus proche du point sur lequel est appelée la
   // fonction.
   double euclide(const pt& p1, const pt& p2, pt* pCloserPt=0) const;

   // Renvoie le point du segment [p1, p2] qui est le plus proche du point sur
   // lequel est appelé la fonction
   pt closerTo(const pt& p1, const pt& p2) const;

   // Ecrit le point dans un flux sous la forme « (x, y) »
   void print(ostream& s) const;
};

//  Insertion dans un flux
ostream& operator<<(ostream& s, const pt& p);



// DEFINITION DES FONCTIONS INLINE
//______________________________________________________________________________

inline const double pt::getX(void) const      
{
    return this->x ;
};

inline const double pt::getY(void) const     
{ return this->y ; };

inline void pt::setX(double x_)                     
{
    this->x = x_ ;
};

inline void pt::setY(double y_)          
{ this->y = y_ ; };


