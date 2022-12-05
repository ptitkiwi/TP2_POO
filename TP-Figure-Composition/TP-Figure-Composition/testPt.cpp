#include "stdafx.h"
#include "pt.h"

void testPt(void);

void testPt(void) // Premiers test des points ___________________________________
{
	//cout << "\nTest de la classe point\n\n" << endl;

	// 1ers tests
	{
		// Construction par défaut et affichage, surcharge ==
		pt p0;
		cout << "p0 = " << p0 << endl;
		assert(p0 == p0);

		// Construction par position
		double x = dRand(-10, 20);
		double y = dRand(-30, 40);
		pt p1(x, y);
		cout << "p1 = " << p1 << endl;
		assert(EPSEQUAL(p1.getX(), x));
		assert(EPSEQUAL(p1.getY(), y));

		// Distance entre points
		double d01 = p0.euclide(p1);
		assert(EPSEQUAL(d01*d01, x*x + y*y));

		// Construction par copie implicite
		pt p2(p1);
		assert(p2 == p1);

		// Affectation implicite
		pt p3(dRand(-50, 60), dRand(-70, 80));
		cout << "p3 = " << p3 << endl;
		p3 = p2;
		cout << "p3 = " << p3 << endl;
		assert(p3 == p2);
	}
	{
		pt p1(dRand(-1000, 1000), dRand(-1000, 1000));
		pt p2(dRand(-1000, 1000), dRand(-1000, 1000));
		pt p3(dRand(-1000, 1000), dRand(-1000, 1000));
	}
	// Déplacement et distance : on construit un triangle rectangle aléatoire et
	// on vérifie le théoreme de Pythagore
	{
		// pT1 : sommet de l'angle droit
		pt pT1(dRand(-1000, 1000), dRand(-1000, 1000));

		// pT2 : à l'horizontal du sommet de l'angle droit
		pt pT2(pT1);
		double dx12 = dRand(-1000, 1000);
		pT2.offset(dx12, 0);

		// pT3 à la verticale du sommet de l'angle droit
		pt pT3(pT1);
		double dy13 = dRand(-1000, 1000);
		pT3.offset(0, dy13);

		// Hypothénuse : pT2-pT3
		double d12 = pT1.euclide(pT2);
		double d13 = pT1.euclide(pT3);
		double d23 = pT2.euclide(pT3);
		assert(EPSEQUAL(d12*d12 + d13*d13, d23*d23)); // Pythagore OK ?
	}
	// Test du point milieu
	{
		pt p1(dRand(-1000, 1000), dRand(-1000, 1000));
		pt p2(dRand(-1000, 1000), dRand(-1000, 1000));
		pt p3 = p1.centerPt(p2);
		assert(EPSEQUAL(p3.euclide(p1), p1.euclide(p2) / 2.0)); // p3 est à égale distance 
		assert(EPSEQUAL(p3.euclide(p2), p1.euclide(p2) / 2.0)); // de p1 et p2
		assert(EPSEQUAL(p1.centerPt(p2).euclide(p1) + p1.centerPt(p2).euclide(p2), p1.euclide(p2)));
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
		double dOpt = p3.euclide(ptCloser);

		for (int i = 0; i < 100; ++i)
		{
			double d01 = dRand(0, 1);
			pt ptTest(p1);
			// On déplace ptTest sur le segment [p1,p2]. Ici on utilise [p1,p2] 
			// comme vectreur directeur
			ptTest.offset(d01*(p2.getX() - p1.getX()), d01*(p2.getY() - p1.getY()));
			double dTest = ptTest.euclide(p3);
			assert(dTest >= dOpt - EPSILON);                // EPSILON nécessaire !
		}
	}
	// Test rotation
	{
		// La rotation d’un point ne change pas sa distance à l’origine
		for (int i = 0; i < 100; ++i)
		{
			pt p8 = pt(dRand(-1000, 1000), dRand(-1000, 1000));
			double d1 = p8.euclide(pt(0, 0));
			p8.rotate90();
			double d2 = p8.euclide(pt(0, 0));
			assert(EPSEQUAL(d1, d2));
		}
	}
	// Symétrie axiale Y
	{
		pt p1(dRand(-1000, 1000), dRand(-1000, 1000));
		pt p2(p1); // clone
		p1.symY();
		// Un point et son symétrique sont à la même distance de (0,0)
		assert(EPSEQUAL(p1.euclide(pt(0, 0)), p2.euclide(pt(0, 0))));
		// symY * symY = id
		p1.symY();
		assert(p1 == p2);
	}
}
