#include "tSgtStack.h"


// Teste si la pile est dans un état valide
// Le nombre de segments doit etre inférieur ou égal a la taille du tableau
// Tous les segments sont inclus dans le cadre rLmit de la figure
bool tSgtStack::valid(void) const
{
	assert(ntSgt <= nDimStack);
	if (ntSgt > 1)
	{
		for (unsigned int i = 0; i + 2 < ntSgt; i++)
		{
			assert(ptSgt[i].getDate() < ptSgt[i + 1].getDate());
		}
	}
	return true;
}

void tSgtStack::expand(void)
{
	assert(valid());

	unsigned long old_nDimStack = nDimStack; //On sauvegarde l'ancienne taille de la pile
	(floor(0.1 * nDimStack) > 8) ? nDimStack = (unsigned long)(1.1 * nDimStack) : nDimStack += 8; // On prend le max entre +10% et +8
	tSgt* expanded_ptSgt = new tSgt[nDimStack]; //On crée une nouvelle pile 10% + grande ou de +8 cases
	for (unsigned int i = 0; i < old_nDimStack; i++)	//On assigne l'ancienne pile à la nouvelle
	{
		expanded_ptSgt[i] = ptSgt[i];
	}
	delete(ptSgt);
	ptSgt = expanded_ptSgt;

	assert(valid());
}

// Constructeurs, Destructeurs, Opérations

tSgtStack::tSgtStack()
	: ptSgt(nullptr)
	, nDimStack(0)
	, ntSgt(0)
{
}

tSgtStack::tSgtStack(const tSgtStack& _t)
	: ptSgt(nullptr)
	, nDimStack(0)
	, ntSgt(0)
{
	this->nDimStack = _t.nDimStack;
	this->ntSgt = _t.ntSgt;
	ptSgt = new tSgt[nDimStack];		// Création de la nouvelle pile copiée de la première
	for (unsigned int i = 0; i < nDimStack; i++)	// Copie de la pile dans la nouvelle pile copiée
	{
		ptSgt[i] = _t.ptSgt[i];
	}
}
/*
tSgtStack::~tSgtStack(void)
{
	assert(valid());
	delete[] ptSgt;
}
*/

bool tSgtStack::operator==(const tSgtStack& t) const
{
	assert(t.valid());
	assert(valid());
	for (unsigned int i = 0; i < ntSgt; i++) {
		if (!(ptSgt[i] == t.ptSgt[i])) {
			return false;
		}
	}
	return(getSize() == t.getSize());	// ntSgt
}

void tSgtStack::operator=(const tSgtStack& t)
{
	this->ptSgt = t.ptSgt;
	this->nDimStack = t.nDimStack;
	this->ntSgt = t.ntSgt;
}

tSgt& tSgtStack::operator[](unsigned long i) const
{
	return(ptSgt[i]);
}

const void tSgtStack::push(const tSgt tseg)
{
	assert(valid());

	if (ntSgt >= nDimStack)   // On vérifie qu'il reste de la place dans la pile
	{
		expand(); // Plus de place, on agrandit la pile
	}
	ptSgt[ntSgt] = tseg; // Ajout du nouveau tSgt dans la pile
	ntSgt++; // Incrémentation du nombre de segments datés
	assert(valid());
}

 const tSgt tSgtStack::top(void) const
{
	assert(ntSgt > 0);
	return(ptSgt[ntSgt-1]);
}

void tSgtStack::pop(void)
{
	ntSgt -= 1;
	ptSgt[ntSgt] = tSgt();
}

void tSgtStack::print(ostream& s) const
{
	if (ntSgt > 0)
	{
		s << "{" << ntSgt << "}" << top() << endl;
		if (ntSgt > 1)
		{
			for (unsigned long i = ntSgt - 1; i > 0; i--)
			{
				s << "<--" << ptSgt[i-1] << endl;
			}
		}
	}
}

ostream& operator<<(ostream& s, const tSgtStack& f)
{
	f.print(s);
	return s;
}
