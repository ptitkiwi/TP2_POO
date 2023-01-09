// main.cpp : définit le point d'entrée pour l'application console.
//
#include "stdafx.h"
void testPt(void);
void testSgt(void);
void testRct(void);
void testFigure(void);
void testTsgt(void);

int main(void)
{
	int nb_tests = 10;
	// Initialisation du générateur aleatoire
	unsigned int rseed = unsigned(time(0)) % 10000;
	//rseed = 5975; 
	srand(rseed);

	// Affichage pour ré-utilisation éventuelle (pour retrouver une série précé-
   // dente afin de reproduire les circonstances exactes d'une erreur en cours
	// de correction)
	cerr << "rseed = " << rseed << "\n" << endl;




	cout << "============================================" << endl;

	// On teste les points
	for (int k = 0; k < nb_tests; ++k) {
		cout << "----------------------------------------" << endl;
		cout << "Test Point " << k + 1 << "/" << nb_tests << " :" << endl;
		cout << endl;
		testPt();
		cout << endl << "*Succesful*" << endl;
	}


	cout << "=================================================================================" << endl;


	// On teste les rectangles
	for (int k = 0; k < nb_tests; ++k) {
		cout << "----------------------------------------"<<endl;
		cout << "Test Rectangle " << k+1 <<"/"<< nb_tests << " :" << endl;
		cout << endl;
		testRct();
		cout<<endl << "*Succesful*" << endl;
	}



	cout << "=================================================================================" << endl;
	// On teste les segments
	for (int k = 0; k < nb_tests; ++k) 
	{
		cout << "----------------------------------------" << endl;
		cout << "Test Segment " << k + 1 << "/" << nb_tests << " :" << endl;
		cout << endl;
		testSgt();
		cout << endl << "*Succesful*" << endl;
	}



	cout << "=================================================================================" << endl;




	// On teste les figures
	//for (int k = 0; k < 10; ++k)
		testFigure();

	return 0;
}