#pragma once

#include "sgt.h"

// Class representing an SGT graph
class graphSgt
{
private:
	// SGT stack associated with the graph
	tSgtStack m_tSgtStack;
	// Boolean indicating whether the graph is selected or not
	bool m_selected;
	// Width of the graph
	double m_width;

public:
	// Default constructor
	graphSgt(void);
	// Constructor taking an SGT object as argument
	graphSgt(sgt _s, double date, double width);

	// Read-only accessor for the SGT object associated with the graph
	const sgt getSgt(void) const;
	// Read-only accessor for the width of the graph
	const double getWidth(void) const;
	// Read-only accessor for the selection state of the graph
	const bool getSelect(void) const;
	// Read-only accessor for the current geometry object
	// (to be implemented)
	const sgt getCurrentGeo(void) const;
	// Read-only accessor for the current time
	const double getCurrentTime(void) const;
	// Read-only accessor for the number of states of the graph
	const double getStateCount(void) const;

	// Mutator for the SGT object associated with the graph
	void setSgt(sgt _s);
	// Mutator for the width of the graph
	void setWidth(double _width);
	// Mutator for the selection state of the graph
	void setSelect(bool _selected);

	// Push a dated segment onto the stack of geometry segments
	void push(const sgt& geo, double date);
	//
	void pop();

	// Function to print the graph to an output stream
	// (to be implemented)
	// void print(ostream _stream) const;


	bool operator==(const graphSgt& A, const graphSgt& B);
	bool operator!=(const graphSgt& A, const graphSgt& B);

	void print(std::ostream& stream) const;

	// Validation function for the graph
	bool valid(void) const;
};



//ostream& operator<<(ostream& _s, const graphSgt& _graphSeg);


// Insertion dans un flux
ostream& operator<<(ostream& s, const graphSgt& gSgt);

//--------------------------------------------------------------------------
//Fonctions inline

// Accesseurs ___________________________________________________________________
// 
// Renvoie le segment
inline const sgt graphSgt::getSegment(void) const{
	return(segment);
};
// Renvoie le taille du segment graphique 
inline const double graphSgt::getWidth(void) const {
	return(width);
};
// Renvoie le(s) segment(s) graphique(s) selectionné(s)
inline const bool graphSgt::getSelected(void) const{
	return(isSelected);
}
inline void graphSgt::setSegment(sgt _segment)
{
	segment = _segment;
}
inline void graphSgt::setWidth(double _width)
{
	width = _width;
}
inline void graphSgt::setSelected(bool _isSelected)
{
	isSelected = _isSelected;
}

