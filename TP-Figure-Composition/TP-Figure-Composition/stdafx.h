// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//
//#define XCODE
#pragma once
#ifdef XCODE 
#define _DEBUG
#endif

#include <iostream>
#include <iomanip>
#include <cassert>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <algorithm>
using namespace std;

// Comparaison des nombres fractionnaires (égalité à EPSILON près)
const double EPSILON = 1.0e-5;
inline bool EPSEQUAL(double a, double b) { return fabs(a - b) < EPSILON; }

// Génération de nombres fractionnaires aléatoire compris entre 0 et d
inline double dRand(double d)
{
   assert( d >= 0 );
   // On génére un double compris dans l'intervalle [0, 1[ , 1 exclus.
   // (attention aux erreurs de débordement arithmétique : RAND_MAX + 1 pourrait
   // devenir égal à INT_MIN dans certaines implémentation !
   double r01 = static_cast<double>(rand())/(static_cast<double>(RAND_MAX) + 1.0);
   double r = d*r01;
   assert( r >= 0 && r <= d ); // Le cas ne peut jamais se produire
   return r;
}

// Génération de nombres entiers aléatoires compris entre 0 et iMax-1 (inclus)
inline long iRand(long iMax)
{ 
	assert( iMax > 0 );
   long iR = static_cast<long>(dRand(iMax));
   assert(iR < iMax);
	return iR;
}

// Génération de nombres fractionnaires aléatoire compris entre min et max
inline double dRand(double min, double max)
{ 
	assert(max - min >= 0);
	return min + dRand(max-min);
}

// Renvoie vrai/faux équiprobables
inline bool bRand(void)
{
   return dRand(1.0) < 0.5;
}

