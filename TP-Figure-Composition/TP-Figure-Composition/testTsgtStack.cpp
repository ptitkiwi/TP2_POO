#include "stdafx.h"
#include "pt.h"
#include "sgt.h"
#include "tSgt.h"
#include "tSgtStack.h"

void testTsgtStack(void);

void testTsgtStack(void)
{

	// Test constructeur
	tSgtStack tSStack1 = tSgtStack();			// Constructeur par défaut

	// Test d'empilement de segment daté
	pt p1(dRand(-1000, 1000), dRand(-1000, 1000));
	pt p2(dRand(-1000, 1000), dRand(-1000, 1000));
	double date = 1;
	sgt s1(p1, p2);
	tSgt ts1 = tSgt(s1, date);
	tSgt ts2 = tSgt(s1, date+1);

	tSStack1.push(ts1);
	tSStack1.push(ts2);
	
	// Test getters
	cerr << endl << "Size of tSStack1 = " << tSStack1.getSize() << endl;

	// Test operator==
	tSgtStack tSStack2 = tSgtStack(tSStack1);	// Constructeur par copie
	assert(tSStack1 == tSStack2);

	// Test d'affichage
	cerr << endl << "tSStack1 = \n" << tSStack1 << endl;

	// Test fonction top
	cerr << endl << "Top stack tSStack1 = \n" << tSStack1.top() << endl;

	// Test fonction pop
	cerr << endl << "tSStack1 = \n" << tSStack1 << endl;
	tSStack1.pop();
	cerr << endl << "tSStack1 = \n" << tSStack1 << endl;
}