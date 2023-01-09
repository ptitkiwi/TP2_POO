#include "stdafx.h"
#include "tSgt.h"
#include "pt.h"
#include "sgt.h"
#include "rct.h"


void testTsgt(void);

void testTsgt(void) 
{
	{
		pt p1(dRand(-1000, 1000), dRand(-1000, 1000));
		pt p2(dRand(-1000, 1000), dRand(-1000, 1000));
		double date = 1;

		sgt s1(p1, p2);
		sgt s2(p1, p2);

		// Test constructeur
		tSgt ts1 = tSgt(s1, date);
		tSgt ts2 = tSgt(s2, date);

		//Test Affichage
		cerr << endl << "ts1 = " << ts1 << endl;
		cerr << endl << "ts2 = " << ts2 << endl;

		// Test operator==
		assert(ts1 == ts2);

		// Test getters
		cerr << endl << "ts1.seg = " << ts1.getSeg() << endl;
		cerr << endl << "ts1.date = @" << ts1.getDate() << endl;


	}
}