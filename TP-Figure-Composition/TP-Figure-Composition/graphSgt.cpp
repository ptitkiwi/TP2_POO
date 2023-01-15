#include "graphSgt.h"


// constructeurs, destructeurs, affectation, égalité ____________________________

graphSgt::graphSgt(tSgt _tseg, double _width)
	:tseg(),
	isSelected(0),
	width(_width)
{
	tseg.push(_tseg);
}

// Construction par défaut : 
graphSgt::graphSgt(void)
	:tseg(),
	isSelected(0),
	width(0)
{
}

bool graphSgt::operator==(const graphSgt& s) const
{
	for (unsigned int i = 0; i < getStateCount(); i++) {
		if (!(this->tseg[i] == s.tseg[i])) 
		{
			return false;
		}
	}
	return (getWidth() == s.getWidth());
}

graphSgt& graphSgt::operator=(const graphSgt& _s)
{
	tseg = _s.tseg;
	width = _s.width;
	isSelected = _s.isSelected;
	return *this;
}

tSgt& graphSgt::operator[](unsigned long i) const
{
	return(tseg[i]);
}

const void graphSgt::push(const tSgt _tseg)
{
	tseg.push(_tseg);
}

void graphSgt::pop(void)
{
	tseg.pop();
}

bool graphSgt::valid(void) const {
	assert(width > 0);
	//assert(segment.valid());  //Not yet defined
	return true;
}

//print au format * SGT(PT( -1305.71, 6604.08 ), PT( -3372.95, 4475.2 ))[1]
void graphSgt::print(ostream& s) const
{
	if (isSelected) {
		s << "* ";
	}
	else {
		s << "  ";
	}
	s << "w(" << width << ")" << tseg;
}

// Insertion d'un segment dans un flux
ostream& operator<<(ostream& f, const graphSgt& s)
{
	s.print(f);
	return f;
};