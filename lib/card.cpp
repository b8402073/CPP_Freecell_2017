#include "card.h"
CardSuit Card::CharToSuit(char inn)
{
	switch(inn)
	{
	case'C': case'c':
		return CLUB;
	case'D': case'd':
		return DIAMOND;
	case'H': case'h':
		return HEART;
	case'S': case's':
		return SPADE;
	default:
		return NONE;
	}
}
int  Card::GetValueFromString(const char* inn)
 {
	 int ret;
	 int sz= strlen(inn);
	 char L2[3];
	 char L1[2];
	 if (sz==2)
	 {
		 L1[0]=inn[0]; L1[1]='\0';
		 ret= atoi(L1);
	 }else if (sz==3)
	 {
		 L2[0]=inn[0]; L2[1]=inn[1]; L2[2]='\0';
		 ret= atoi(L2);
	 }else
		 return 0;
	 if (ret>=1 && ret<=13)
		 return ret;
	 return 0;	 
 }
 CardSuit  Card::GetSuitFromString(const char* inn)
 {
	 int sz= strlen(inn);
	 char C;
	 if (sz==3)
		 C=inn[2];
	 else if (sz==2)
		 C=inn[1];
	 else
		 return NONE;
	 return Card::CharToSuit(C);
 }
Card GetCard(byte value,CardSuit suit)
{
	if (value>=1 && value<=13 && suit>=CLUB && suit<=SPADE)
	{
		return CardDeck[ (value-1)*4+suit+1 ];
	}
	return CardDeck[_Empty];
}
Card GetCard(string inn) 
{
	if (inn!="") {
		int V=Card::GetValueFromString(inn.c_str());
		CardSuit S=Card::GetSuitFromString(inn.c_str());
		if (V>=1 && V<=13 && S!=NONE)
			return GetCard(V,S);
	}
	return _Empty;
}

Card::Card(byte inn)
: MyByte(inn) {}

byte Card::GetValue() const
{
	CC tmp=(CC) MyByte;
	switch(tmp)
	{
	case C1: case D1: case H1: case S1:  return 1;
	case C2: case D2: case H2: case S2:  return 2;
	case C3: case D3: case H3: case S3:  return 3;
	case C4: case D4: case H4: case S4:  return 4;
	case C5: case D5: case H5: case S5:  return 5;
	case C6: case D6: case H6: case S6:  return 6;
	case C7: case D7: case H7: case S7:  return 7;
	case C8: case D8: case H8: case S8:  return 8;
	case C9: case D9: case H9: case S9:  return 9;
	case C10: case D10: case H10: case S10:  return 10;
	case C11: case D11: case H11: case S11:  return 11;
	case C12: case D12: case H12: case S12:  return 12;
	case C13: case D13: case H13: case S13:  return 13;
	default:
		return 0;
	}
}
CardSuit Card::GetSuit() const
{
	CC tmp=(CC) MyByte;
	switch(tmp)
	{
	case C1: case C2: case C3: case C4: case C5: case C6: case C7: case C8:
	case C9: case C10: case C11: case C12: case C13:
		return CLUB;
	case D1: case D2: case D3: case D4: case D5: case D6: case D7: case D8:
	case D9: case D10: case D11: case D12: case D13:
		return DIAMOND;	
	case H1: case H2: case H3: case H4: case H5: case H6: case H7: case H8:
	case H9: case H10: case H11: case H12: case H13:
		return HEART;	
	case S1: case S2: case S3: case S4: case S5: case S6: case S7: case S8:
	case S9: case S10: case S11: case S12: case S13:
		return SPADE;
	default:
		return NONE;
	}
}
string Card::_str() const
{
	return _CardString[MyByte];
}
string Card::str() const
{
	if (MyByte>= C10)
		return _str();
	return _str().substr(1,2);
}
bool Card::isRed() const
{
	CardSuit s=GetSuit();
	return (s==DIAMOND || s==HEART);
}

Card::Card(const Card& that)
:MyByte(that.MyByte)
{
}
Card::Card()
:MyByte(0)
{
}
void copy_2d_arr(Card dst[][21],const Card src[][21])
{
	for (int i=0; i<8; i++)
	{
		for(int j=0; j<21; j++)
		{
			dst[i][j]= src[i][j];
		}
	}
}
bool CompareCardArr(const Card thes[][21], const Card src[][21])
{
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<21; j++)
		{
			if (thes[i][j] != src[i][j])
				return false;
		}
	}
	return true;
}
string Card::estr() const
{
	static string _SuitChar_[]={"C","D","H","S","@"};
	char tmp[3];
	string ret;
	switch(MyByte)
	{
	case _Empty:  ret="_Empty"; return ret;
	case _EndOfStream: ret="_EndOfStream"; return ret;
	default:
		ret= _SuitChar_[ this->GetSuit() ] + itoa(this->GetValue(),tmp,10);
	}
	return ret;
}
