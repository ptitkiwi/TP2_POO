#include "graphSgt.h"


// constructeurs, destructeurs, affectation, égalité ____________________________

graphSgt::graphSgt(sgt _segment)
	:segment(_segment),
	isSelected(0),
	width(0)
{
}

// Construction par défaut : 
graphSgt::graphSgt(void)
	:segment(),
	isSelected(0),
	width(0)
{
}

bool graphSgt::operator==(const graphSgt& s) const
{
	return (
		getSelected() == s.getSelected()
		&& getSegment() == s.getSegment()
		&& getWidth() == s.getWidth()
		);
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
		s << "* "<< segment << "["<<width<<"]";
	}
	else {
		s << "  " << segment << "[" << width << "]";
	}
	
}

// Insertion d'un segment dans un flux
ostream& operator<<(ostream& f, const graphSgt& s)
{
	s.print(f);
	return f;
};