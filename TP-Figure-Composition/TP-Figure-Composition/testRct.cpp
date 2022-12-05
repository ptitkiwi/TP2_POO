#include "stdafx.h"
#include "pt.h"
#include "sgt.h"
#include "rct.h"



void testRct(void)// Test des rectangles
{
	//cout << "\nTest de la classe rectangle\n\n" << endl;

	//Test constructeur par défaut :
	{
		rct r0;

		assert(r0.getCenterPt() == pt(0, 0));
		assert(!(r0.getCenterPt() == pt(0, 1)));

		assert(EPSEQUAL(r0.getHeight(), 0.0));
		assert(EPSEQUAL(r0.getWidth(), 0.0));

		assert(EPSEQUAL(r0.x1(), 0.0));
		assert(EPSEQUAL(r0.x2(), 0.0));
		assert(EPSEQUAL(r0.y1(), 0.0));
		assert(EPSEQUAL(r0.y2(), 0.0));

		/* Test affichage :
		cout << "r0 = ";
		r0.print(cout);
		cout << endl;
		*/

		cout << "r0 = " << r0 << endl;

	}
	//Test constructeur à partir des bords [x1..x2]x[y1..y2] 
	{
		double x1 = dRand(-100, 100);
		double x2 = x1 + dRand(100);
		double y1 = dRand(-100, 100);
		double y2 = y1 + dRand(100);

		rct r0(x1, x2, y1, y2);

		assert(pt((x1 + x2) / 2, (y1 + y2) / 2) == r0.getCenterPt());
		assert(EPSEQUAL(r0.getWidth(),(x2 - x1)));
		assert(EPSEQUAL(r0.getHeight(), (y2 - y1)));

		//test surface
		assert(EPSEQUAL(r0.area(), ((x2 - x1) * (y2 - y1))));

		//test Inflate
		double oldArea = r0.area();
		double px = dRand(2);
		double py = dRand(2);
		r0.inflate(px, py);
		assert(EPSEQUAL(r0.area(), oldArea * px * py));


		/* Test affichage :
		cout << "r0 = ";
		r0.print(cout);
		cout << endl;
		*/
		cout << "r0 = " << r0 << endl;

	}
	//Test Construction à partir de deux points absolument quelconques : le plus pe-
	// tit rectangle qui contient les deux points.
	{
		double x1 = dRand(-100, 100);
		double x2 = dRand(-100, 100);
		double y1 = dRand(-100, 100);
		double y2 = dRand(-100, 100);

		pt p1(x1, y1);
		pt p2(x2, y2);

		rct r0(p1,p2);


		assert(pt((x1 + x2) / 2, (y1 + y2) / 2) == r0.getCenterPt());
		assert(EPSEQUAL(r0.getWidth(), abs(x2 - x1)));
		assert(EPSEQUAL(r0.getHeight(), abs(y2 - y1)));

		assert(EPSEQUAL(r0.x1(), min(x1, x2)));
		assert(EPSEQUAL(r0.x2(), max(x1, x2)));
		assert(EPSEQUAL(r0.y1(), min(y1, y2)));
		assert(EPSEQUAL(r0.y2(), max(y1, y2)));

		//test égalité
		assert(r0 == r0);
		rct r1(r0);//Clone
		assert(r1 == r0);
		assert(r0 == r1);

		//Test point aléatoire intérieur du rectangle
		for (unsigned int i = 0; i < 100; i++)
		{
			pt p0 = r0.randPt();
			p0.offset(r0.getWidth() + 2 * EPSILON, r0.getHeight() + 2 * EPSILON);
			assert(!(r0.contains(p0)));


			rct r1 = r0.randRct();
			//on déplace r1, forcément un peu à l'extérieur de r0
		}

		//Test Euclide

		pt p0 = r0.getCenterPt();
		assert(EPSEQUAL(r0.euclide(p0), 0));
		p0.offset(0, r0.getHeight());
		assert(EPSEQUAL(r0.euclide(p0), r0.getHeight() / 2));
		p0.offset(r0.getWidth(), 0);
		assert(EPSEQUAL(r0.euclide(p0), sqrt(pow(r0.getWidth() / 2, 2) + pow(r0.getHeight() / 2, 2))));
		p0.offset(0,-r0.getHeight());
		assert(EPSEQUAL(r0.getCenterPt().getY(), p0.getY()));
		assert(EPSEQUAL(r0.euclide(p0), r0.getWidth() / 2));
		/* Test affichage :
		cout << "r0 = ";
		r0.print(cout);
		cout << endl;
		*/
		cout << "r0 = " << r0 << endl;

	}

}
