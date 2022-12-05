#include "stdafx.h"
#include "pt.h"
#include "sgt.h"
#include "rct.h""
void testSgt(void);

void testSgt(void) // Les segments _____________________________________________
{
	//cout << "\nTest de la classe segment\n\n" << endl;
	// 1er tests
	{
		//Init
		sgt s0;
		pt p1(dRand(-1000, 1000), dRand(-1000, 1000));
		pt p2(dRand(-1000, 1000), dRand(-1000, 1000));
		
		//Test Constructeur
		sgt s1(p1, p2);

		//Test Affichage
		cerr << endl << "s1 = " << s1 << endl;

		//Test ==
		assert(s0 == s0);

		//Test des get
		pt pp1 = s1.get_p1();
		assert(pp1 == p1);
		pt pp2 = s1.get_p2();
		assert(pp2 == p2);
		
		//Test des set
		s1.set_p1(p2);
		assert(s1.get_p1() == p2);
		s1.set_p2(p1);
		assert(s1.get_p2() == p1);

		//Test de x1,x2,y1,y2
		rct r1(p1, p2);
		rct r2(s1.x1(), s1.x2(), s1.y1(), s1.y2());
		assert(r1 == r2);
		
		//Test de length
		assert(EPSEQUAL(s1.length(), r1.bottomLeft().euclide(r1.topRight())));
		sgt s3(pt(0, 0), pt(1, 2));
		assert(EPSEQUAL(s3.length(), sqrt(5.0)));

		//Test Center Point
		assert(s1.centerPt() == r2.getCenterPt());

		//Test Offset (On vérifie que offset ne modifie pas la longueur du segment)
		sgt s4(s1);
		double dx = dRand(-1000, 1000);
		double dy = dRand(-1000, 1000);
		assert(EPSEQUAL(s1.length(), s4.offset(dx, dy).length()));
		//Test Offset (On vérifie que l'offset dx dy du centre du semgetn est égal au centre du segment après offset (dx,dy)
		sgt s5(s1);
		assert(s1.centerPt().offset(dx, dy) == s5.offset(dx, dy).centerPt());

		//Test affectation
		s0 = s1;
	}

	// Test closerTO
	{
		// On vérifie closerTo en générant 3 points aléatoires p1, p2 et p3. 
		// On calcule pClose le point du segment [p1,p2] le plus proche de p3.
		// Puis on vérifie qu'une sélection d'autres points aléatoires du segment
		// [p1,p2] sont tous plus éloignés.

		pt p1(dRand(-1000, 1000), dRand(-1000, 1000));
		pt p2(dRand(-1000, 1000), dRand(-1000, 1000));
		pt p3(dRand(-1000, 1000), dRand(-1000, 1000));
		pt ptCloser = p3.closerTo(p1, p2);

		sgt s12(p1, p2);
		pt ptOpt = s12.closerTo(p3);
		assert(ptOpt == ptCloser);

		double dOpt = p3.euclide(ptCloser);

		for (int i = 0; i < 100; ++i)
		{
			pt pTest = s12.randPt();
		}
	}

}



