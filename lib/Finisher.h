#include "card.h"
#ifndef FINISHER_H
#define FINISHER_H
class Finisher
{
private:
	Card  arr[4];
	bool  DoResponseCard(Card inn);
	

public:
	Finisher();
	Finisher(const Finisher& inn);
	Finisher(Card,Card,Card,Card);
	//Finisher(string,string,string,string);
	Finisher(const Card that[]);
	Finisher* copy() const;
	bool  add(Card inn);
	Card  Need(CardSuit inn) const;
	bool  Needed(Card inn) const;
	string str() const;
	bool  SafeCardUp(Card inn) const;
	bool  equals(const Finisher* that) const;
	Card  Top(CardSuit inn) const;
	bool  Search(Card that) const;
};
#endif
