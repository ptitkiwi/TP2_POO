#include "tSgt.h"

tSgt::tSgt(void)
	:seg()
	,date(0)
{
}

tSgt::tSgt(graphSgt _seg, double _date)
	:seg(_seg)
	,date(_date)
{
}

bool tSgt::operator==(const tSgt& s) const
{
	return (
		getSeg() == s.getSeg()
		&& getDate() == s.getDate()
		);
}

// Ecriture dans un flux au format : SGT(( pt1.X, pt1.Y ), ( pt2.X, pt2.Y ))@date
void tSgt::print(ostream& s) const
{
	s << "  " << seg << "@" << date;
}

ostream& operator<<(ostream& s, const tSgt& f)
{
	f.print(s);
	return s;
}
