#include "stdafx.h"
#include "figure.h"


void testFigure(void)
{
	cout << "\nTest de la classe figure\n\n" << endl;

	// On initialise un rectangle cadre de dimension et de position aléatoires
	rct rcLimit(0, dRand(1000, 10000), 0, dRand(1000, 10000));
	assert(rcLimit.valid());

	//On créé rCadre de 20% de plus que rcLimit
	rct rCadre(0, floor(1.2 * rcLimit.x2()), 0, floor(1.2 * rcLimit.y2()));

	// On constuit une figure vide délimitée par ce rectangle et on l'affiche
	figure f(rCadre);
	assert(f.valid());

	cout << "Figure f :" << f << endl;

	// on ajoute un nombre aléatoire de segments dans la figure f
	unsigned int nb_setSelected = 0;
	unsigned int t = 0;
	for (int i = 10; i > 0; i--)
	{
		f.setPenWidth(i);
		sgt newSgt = rCadre.randSgt();
		tSgt tSgt1 = tSgt(newSgt, t);
		unsigned res = f.add(tSgt1);
		t++;
	}

	// décompte de nombre de segments 
	cout << f << endl;
	cout << "nombre de segments selectionnes = " << f.getNbrSelected() << endl;
	assert(f.getNbrSelected() == nb_setSelected);

	/*
	cout << "\nTest de la classe figure\n\n" << endl;

	// On initialise un rectangle cadre de dimension et de position aléatoires
	rct rcLimit(0, dRand(1000, 10000), 0, dRand(1000, 10000));

	//On agrandit rcLimit de 20%
	rct rCadre( 0, floor(1.2 * rcLimit.x2()), 
		0, floor(1.2 * rcLimit.y2()));
	
	// On construit une figure vide délimitée par ce rectangle et on l'affiche
	figure f1(rCadre);

	//Test Add et affichage
	
	int nb_test_boucle = round(dRand(10, 20));
	cerr << "=============  Test Print segments :  =============" << endl;
	for (int i = 0; i < nb_test_boucle; i++) {
		sgt s1(rCadre.randSgt());
		double d = i;
		tSgt ts1(s1, d);
		//On assigne aléatoirement une valeur aléatoire pour width et selected
		f1.setPenWidth(dRand(0, 50));	
		f1.add(ts1);
		f1[i].setSelected(bRand());
		cerr <<f1[i] << endl;
	}
	assert(f1.valid());
	cerr << endl<<"=============  Test Print Figure :  =============" << endl;
	cerr << f1 << endl;

	//Test Proche de

 	// On génére un point de référence aléatoire dans le rectangle cadre pour 
	// distinguer les segments de la figure en segments "proches" de ce point et
	// les autres
	figure f2(rCadre);
	pt pt_ref = f2.getRctLimit().randPt();
	unsigned long dist = dRand(0, 0.5*f2.getRctLimit().perimeter());

	cerr << endl << "=============  Test fonction proche de " << pt_ref << " a une distance de "<<dist <<"  =============" << endl;
	
	for (int i = 0; i < nb_test_boucle; i++) {
		tSgt s1(rCadre.randSgt());
		double d = i;
		tSgtStack ts1(s1, d);
		//On assigne aléatoirement une valeur aléatoire pour width
		f2.setPenWidth(dRand(0, 50));
		f2.add(ts1);
		//Test de la distance au point le plus proche du segment
		if (pt_ref.euclide(s1.closerTo(pt_ref))) {
			f2[i].setSelected(bRand());
		}
	}
	cerr << f2 << endl;

	//Test Remove :
	cerr << endl << "=============  Test de remove :  =============" << endl;
	unsigned long oldNSelected = f2.getNbrSelected();
	unsigned long oldNSize= f2.getSize();
	unsigned long nSgtRemoved = f2.remove();//On supprime tous les segments selecionnés (ici tous les proches de pt_ref)
		//Tests aasert
	assert(nSgtRemoved == oldNSelected);//On vérifie que le nombre de segments supprimés correspondant au nombre de segment précedemment séléctionnés
	assert(f2.getSize() == (oldNSize - oldNSelected)); //On vérifie que la nouvelle taille est cohérente
		//Affichage
	cerr << f2 << endl;

	//Test Remove all
	cerr << endl << "=============  Test de remove all:  =============" << endl;
	for (int i = 0; i < f2.getSize(); i++) {
		f2[i].setSelected(true);
	}
	f2.remove();//On supprime tous les segments
	cerr << f2 << endl;


	//Test copie et égalité
	cerr << endl << "=============  Test de copie:  =============" << endl;
	figure g1 = f1;
	assert(f1 == g1);
	cerr << f1<< endl << g1 << endl;
	
	f1 == g1 ? (cerr << "==> Les deux figures sont identiques" << endl) : (cerr << "==> Les deux figures sont differentes" << endl);
	
	//Test copie - Non modif de l'original
	cerr << endl << "=============  Test de non modification de l'original :  =============" << endl;
	g1.remove();
	cerr << f1<< endl << g1 << endl;

	f1 == g1 ? (cerr << "==> Les deux figures sont identiques" << endl) : (cerr<< "==> Les deux figures sont differentes" << endl);

*/
}
