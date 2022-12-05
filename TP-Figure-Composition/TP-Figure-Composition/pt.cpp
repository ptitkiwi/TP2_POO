#include "stdafx.h"
#include "pt.h"

pt::pt(void) // Construction par défaut
	: x(0)
	, y(0)
{ }


pt::pt(double x_, double y_) // Créée à partir de ses coordonnées
	: x(x_)
	, y(y_)
{ }

// Egalité de deux points
bool pt::operator==(const pt& p2) const
{
	return EPSEQUAL(this->x, p2.x) && EPSEQUAL(this->y, p2.y);
}

// Translate le point de (dx,dy) 
void pt::operator+=(const pt& p2)
{
	this->offset(p2.x, p2.y);
}

//Compare les normes euclidiennes de deux points
bool pt::operator<(const pt& p2)
{
	return this->euclide(pt(0, 0)) < p2.euclide(pt(0, 0));
}


double pt::euclide(const pt& p2) const
{
	return sqrt((this->x - p2.x)*(this->x - p2.x)
		+ (this->y - p2.y)*(this->y - p2.y));
}

// Translate le point de (dx,dy) 
pt& pt::offset(double dx, double dy)
{
	this->x += dx; this->y += dy;
	return *this;
}


// Calcule le point milieu du segment aboutissant au point argument.
pt pt::centerPt(const pt& p2) const
{
	return pt((this->x + p2.x) / 2.0, (this->y + p2.y) / 2.0);
}

// Rotation de 90° dans le sens positif
pt& pt::rotate90(void)
{
	*this = pt(-y, x);
	return *this;
}
// Effectue une symétrie par rapport à l'axe Y et se renvoie lui-même
pt& pt::symY(void)
{
	x = -x;
	return *this;
}

ostream& operator<<(ostream& s, const pt& p)
{
	p.print(s);
	return s;
}

// Ecrit ce point-ci dans un flux sous la forme « PT(x, y) »
void pt::print(ostream& s) const
{
	s << setiosflags(ios::fixed) << setprecision(2);
	s << "( " << setw(8) << this->x << ", " << setw(8) << this->y << " )";
}

// Renvoie la distance de ce point au segment de droite [p1, p2]. Au retour,
// si le pointeur closerPt est non nul, alors *closerPt sera égal au point du
// segment [p1, p2] le plus proche.
double pt::euclide(const pt& p1, const pt& p2, pt* closerPt) const
{
	// On passe en représentation paramétrique de la droite passant par les 
	// deux points p1 et p2 : p(t) = p1 + t*(p2-p1)
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	pt ptOpt;

	if (p1.euclide(p2) < EPSILON) // Le segment [p1, p2] est dégénéré
	{
		ptOpt = p1;
	}
	else
	{
		// On calcule la valeur de "t" qui minimise la distance.
		double t = ((x - p1.x) * dx + (y - p1.y) * dy) / (dx*dx + dy*dy);

		// Si 0<= t <= 1; P(t) se trouve sur le segment [p1, p2].
		// Si t < 0, p1 est le plus proche de ce point-ci.
		// Si t > 1, p2 est le plus proche de ce point-ci

		if (t < 0) // Le point le plus proche est p1
			ptOpt = p1;

		else if (t > 1) // Le point le plus proche est p2
			ptOpt = p2;

		else // Le point le plus proche se trouve sur le segment (p1,p2)
			ptOpt = pt(p1.x + t*dx, p1.y + t*dy);
	}
	// On affecte le point argument s'il y a lieu
	if (closerPt)
		*closerPt = ptOpt;

	// On retourne la distance de ce point-ci au point le plus proche
	return this->euclide(ptOpt);
}

// Renvoie le point du segment [p1,p2] qui est le plus proche de ce point-ci
pt pt::closerTo(const pt& p1, const pt& p2) const
{
	pt pClose;
	euclide(p1, p2, &pClose);
	return pClose;
}

