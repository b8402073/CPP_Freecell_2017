#include "Finisher.h"
bool Finisher::DoResponseCard(Card inn) 
{
	assert(inn>_Empty);
	arr[(int) inn.GetSuit()]=inn;
	return true;
}
Card Finisher::Top(CardSuit inn) const
{
	if (inn!=NONE)
		return arr[inn];
	return _Empty;
}
bool Finisher::Search(Card that) const
{
	if (that==_Empty)
		return false;
	Card response=Top(that.GetSuit());
	if (response==_Empty)
		return false;
	else if (that.GetValue() > response.GetValue() )
		return false;
	return true;
}
Finisher::Finisher() {}
Finisher::Finisher(Card c,Card d,Card h,Card s)
{
	int flag=0;
	if (c==_Empty || c.GetSuit()==CLUB)
	{
		arr[0]=c; flag++;
	}
	if (d==_Empty || d.GetSuit()==DIAMOND)
	{	arr[1]=d; flag++;
	}
	if (h==_Empty || h.GetSuit()==HEART)
	{	arr[2]=h; flag++;
	}
	if (s==_Empty || s.GetSuit()==SPADE)
	{	arr[3]=s; flag++;
	}
	if (flag==4)
		return;
	throw runtime_error("Bad Finisher Input");	
}
Finisher::Finisher(const Card that[])
{
	assert(that[0].GetSuit()==NONE || that[0].GetSuit()== CLUB);
	assert(that[1].GetSuit()==NONE || that[1].GetSuit()== DIAMOND);
	assert(that[2].GetSuit()==NONE || that[2].GetSuit()== HEART);
	assert(that[3].GetSuit()==NONE || that[3].GetSuit()== SPADE);
	std::copy(that,that+4,arr);
}
Finisher::Finisher(const Finisher& inn)
{
	std::copy(inn.arr,inn.arr+4,arr);	
}

Finisher* Finisher::copy() const
{
	Finisher* ret=new Finisher(arr);
	return ret;
}
bool Finisher::add(Card inn)
{
	if (inn!=_Empty)
	{
		Card that=Top(inn.GetSuit());
		if (that==_Empty && inn.GetValue()==1)
			return DoResponseCard(inn);
		else if (inn.GetValue()== that.GetValue()+1)
			return DoResponseCard(inn);
	}
	return false;
}
Card Finisher::Need(CardSuit inn) const
{
	assert(inn!=NONE);
	Card that=Top(inn);
	if (that==_Empty)
		return GetCard(1,inn);
	else if (that.GetValue()<13)
		return GetCard(that.GetValue()+1, inn);
	else
		return _Empty;	
}
bool Finisher::Needed(Card inn) const
{
	if (inn==_Empty)
		return false;
	if (inn==(Need(inn.GetSuit())))
		return true;
	return false;
}
string Finisher::str() const
{
	string ret("[");
	for (int i=0; i<3; i++)
	{
		if (arr[i]==_Empty)
			ret+="EMPTY,";
		else
		{	
			ret+= (arr[i].str() );
			ret+= ",";
		}
	}
	if (arr[3]==_Empty)
		ret+="EMPTY";
	else
		ret+=(arr[3]).str();
	ret+= "]";
	return ret;
}
bool  Finisher::SafeCardUp(Card inn) const
{
	if (inn!= _Empty)
	{
		int N=inn.GetValue();
		if (N==1 || N==2)
			return true;
		if (inn.isRed())
		{
			if (arr[CLUB]==0 ||	arr[SPADE]==0)
				return false;
			if (arr[SPADE].GetValue()>= inn.GetValue()-1  &&
				arr[CLUB].GetValue()>= inn.GetValue()-1)
				return true;
			return false;
		}else
		{
			if (arr[DIAMOND]==0 || arr[HEART]==0)
				return false;
			if (arr[DIAMOND].GetValue()>=inn.GetValue()-1 &&
				arr[HEART].GetValue()>= inn.GetValue()-1)
				return true;
			return false;
		}
	}
	return false;
}
bool Finisher::equals(const Finisher* that) const
{
	if (that!=NULL)
	{
		return( arr[0]==that->arr[0] &&
			    arr[1]==that->arr[1] &&
				arr[2]==that->arr[2] &&
				arr[3]==that->arr[3] );
	}
	return false;
}
