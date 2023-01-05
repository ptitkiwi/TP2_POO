#include "graphSgt.h"


// constructeurs, destructeurs, affectation, égalité ____________________________

graphSgt::graphSgt(sgt _segment)
	:segment(_segment),
	isSelected(0),
	width(0)
{
}

graphSgt::graphSgt(sgt _s, double date, double width) :
{
	m_tSgtStack.push(const sgt& _s, double date);
	m_selected = 0;
	m_width = width;
}
const int graphSgt::getCurrentGeo(void) const
{
	return 0;
}

const double graphSgt::getCurrentTime(void) const
{
	tSgt temp_tsgt;
	temp_tsgt = m_tSgtStack.back();
	return temp_sgt.date;
}

const double graphSgt::getStateCount(void) const
{
	return m_tSgtStack.size();
}

void push(const sgt& geo, double date)
{
	m_tSgtStack.push(tSgt new tsgt(geo, date); //TODO
}

bool operator==(const graphSgt& A, const graphSgt& B)
{
	// The stacks must have the same size
	if (A.m_tSgtStack.size() != B.m_tSgtStack.size())
	{
		return false;
	}

	// Compare each element of the left stack to its counterpart in the right stack
	for (size_t i = 0; i < A.m_tSgtStack.size(); ++i)
	{
		if (A.m_tSgtStack[i] != B.m_tSgtStack[i])
		{
			return false;
		}
	}

	// If all elements are equal and the widths are equal, then the objects are equal
	return A.m_width == B.m_width;
}

bool operator!=(const graphSgt& A, const graphSgt& B)
{
	return !(A == B);
}

bool graphSgt::valid(void) const {
	assert(width > 0);
	//assert(segment.valid());  //Not yet defined
	return true;
}

void print(std::ostream& stream) const
{
	// Print the selection marker and stroke width
	stream << (m_selected ? "* " : "  ") << "w(" << m_width << ") ";

	// Print the stack of states
	stream << "{" << m_tSgtStack.size() << "}";
	for // A DEFINIR
	{
		stream << "<--SGT" << /*COORDONNES SEGMENT*/ << "@" << /*DATE*/;
	}

	stream << std::endl;
}

// Insertion d'un segment dans un flux
ostream& operator<<(ostream& f, const graphSgt& s)
{
	s.print(f);
	return f;
};