#include "stdafx.h"
#include "rct.h"
#include <cassert>

bool rct::valid(void) const
{	
	assert(w >= 0);
	assert(h >= 0);
	return true;
}

rct::rct(void)
	:pC()
	,h(0)
	,w(0)
{
	assert(valid());
}

rct::rct(const double x1, const double x2, const double y1, const double y2)
	:pC( ((x1+x2)/2.0) , ((y1+y2)/2.0))
	,w(x2 - x1)
	,h(y2 - y1)
{
	assert(valid());
}

rct::rct(const pt p1, const pt p2)
	:pC(p1.centerPt(p2))
	,w(abs(p2.getX()-p1.getX()))
	,h(abs(p2.getY() - p1.getY()))
{
	assert(valid());
}

rct& rct::offset(const double dx, const double dy)
{
	assert(valid());
	pC.offset(dx, dy);
	assert(valid());
	return *this;
}

// Ecrit le rectangle dans le flux argument au format RCT[x1, x2]x[y1, y2]
void rct::print(ostream& s) const
{	
	assert(valid());
	s << "RCT[" << x1() << ", " << x2() << "]x[" << y1() << ", " << y2() << "]";
}

// Operateur d'insertition dans un flux :
ostream& operator<<(ostream& s, const rct& rc)
{
	rc.print(s);
	return s;
}

// Deux rectangles sont égaux s'ils ont les mêmes limites
bool rct::operator==(const rct& r2) const {
	assert(valid());
	assert(r2.valid());
	return(
		pC == r2.pC
		&&
		EPSEQUAL(h, r2.h)
		&&
		EPSEQUAL(w, r2.w)
		);
}

pt rct::randPt(void) const {
	assert(valid());
	pt pTRand = pt(dRand(x1(), x2()), dRand(y1(), y2()));
	assert(contains(pTRand));
	return pTRand;
}

sgt rct::randSgt(void) const
{
	return sgt(randPt(), randPt());
}

bool rct::contains(const pt& p) const {
	assert(valid());
	return((p.getX() + EPSILON >= x1() && p.getX() <= x2() + EPSILON)
		&&
		(p.getY() + EPSILON >= y1() && p.getY() <= y2() + EPSILON)
		);
}

// Renvoie vrai ssi le segment argument est dans le rectangle 
bool rct::contains(const sgt& s) const
{
	assert(valid());
	return(
		contains(s.get_p1())
		&& contains(s.get_p2())
		);
}

bool rct::contains(const rct& r2) const {
	assert(valid());
	assert(r2.valid());
	return	(contains(r2.bottomLeft()) && contains(r2.topRight()));
}

void rct::inflate(const double px, const double py)
{
#ifdef _DEBUG
	pt pC0 = pC;
#endif
	assert(valid());
	assert(px >= 0);
	assert(py >= 0);

	w*= px;
	h*= py;

	assert(pC0 == pC);
	assert(valid());
}

double rct::euclide(const pt& ptRef) const
{
	assert(valid());
	if (contains(ptRef))
		return 0.0;

	double d11 = ptRef.euclide(topLeft(), topRight());
	double d00 = ptRef.euclide(bottomLeft(), bottomRight());
	double d01 = ptRef.euclide(topLeft(), bottomLeft());
	double d10 = ptRef.euclide(bottomRight(), topRight());
	return min(min(d11, d00), min(d01, d10));
}

// Renvoie un rectangle aléatoire contenu dans le rectangle
rct rct::randRct(void) const {
	assert(valid());
	rct r0(randPt(), randPt());
	assert(contains(r0));
	return r0;
}