#include "stdafx.h"
#include "sgt.h"

//Constructeurs _______________________________________________________________
//Construction par défaut : les deux extrémités se trouvent à l'origine
sgt::sgt(void)
	: p1()
	, p2()
{
}
// Constuction à partir de deux points
sgt::sgt(const pt& p1_, const pt& p2_)
	: p1(p1_)
	, p2(p2_)
{
}

//Opérateur ==
bool sgt::operator==(const sgt& s2) const 
{
	return (p1 == s2.get_p1() && p2 == s2.get_p2());
}

//Fonctions
pt sgt::centerPt(void) const
{
	return p1.centerPt(p2);
}

double sgt::length(void) const
{
	return p1.euclide(p2);
}

sgt& sgt::offset(double dx, double dy) 
{
	p1.offset(dx, dy);
	p2.offset(dx, dy);
	return *this; //Comme l'objet d'appel est en référence, on revenoie la valeur de l'objet d'appel
	//return sgt() ne fonctionne pas, car c'est une varibale locale, et est donc détruire après le return
}

void sgt::print(ostream& s) const
{
	s << "SGT(" << p1 << ", " << p2;
}

// Insertion d'un segment dans un flux
ostream& operator<<(ostream& f, const sgt& s)
{
	s.print(f);
	return f;
};

// Renvoie un point situé sur le segment qui est le plus proche du point argument
pt sgt::closerTo(pt p) const
{
	return p.closerTo(p1, p2);
}

// Renvoie un point aléatoire situé sur le segment
pt sgt::randPt(void) const
{
	double d01 = dRand(0, 1);
	pt ptRnd(p1);
	//On déplace ptRnd sur le segment [p1,p2]. Ici on utilise [p1,p2] comme vecteur directeur
	ptRnd.offset(d01 * (p2.getX() - p1.getX()), d01 * (p2.getY() - p1.getY()));

	//Le point ptRnd se trouve sur le segment d'appe <=> sa ditance au segment est nulle
	assert(ptRnd.euclide(p1, p2) < EPSILON);
	return pt();
}

