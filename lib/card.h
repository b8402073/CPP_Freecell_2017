#include <cassert>
#include <cstring>
#include <string>
#include <iostream>

#ifndef CARD_H
#define CARD_H
using namespace std;
static string _CardString[]={"   "," 1C"," 1D"," 1H"," 1S",
		    " 2C"," 2D"," 2H"," 2S",
		    " 3C"," 3D"," 3H"," 3S",
		    " 4C"," 4D"," 4H"," 4S",
		    " 5C"," 5D"," 5H"," 5S",
		    " 6C"," 6D"," 6H"," 6S",
		    " 7C"," 7D"," 7H"," 7S",
		    " 8C"," 8D"," 8H"," 8S",
		    " 9C"," 9D"," 9H"," 9S",
		    "10C","10D","10H","10S",
		    "11C","11D","11H","11S",
		    "12C","12D","12H","12S",
		    "13C","13D","13H","13S"	};

//static string SuitChar[]={"c","d","h","s","@"};//可以考慮放在function內
enum CardSuit
{	CLUB,DIAMOND,HEART,SPADE,NONE 	
};

enum CC {
		_Empty,C1,D1,H1,S1,
			 C2,D2,H2,S2,
			 C3,D3,H3,S3,
			 C4,D4,H4,S4,
			 C5,D5,H5,S5,
			 C6,D6,H6,S6,
			 C7,D7,H7,S7,
			 C8,D8,H8,S8,
			 C9,D9,H9,S9,
			 C10,D10,H10,S10,
			 C11,D11,H11,S11,
			 C12,D12,H12,S12,
			 C13,D13,H13,S13
			 , _EndOfStream=84
};
typedef __int8 byte;
union Card
{
public:
	byte MyByte;	
	Card(byte inn);                //done
	string _str() const;			//done
	string str() const;				//done
	string estr() const;			//直接印出與Enum相同的字串
	byte GetValue() const;			//done
	CardSuit GetSuit() const;		//done
	bool isRed() const;				//done
	Card(const Card& that);			//done
	Card();							//done
	operator int() const { return MyByte;}
	static	CardSuit GetSuitFromString(const char* inn);   //done
	static  int      GetValueFromString(const char* inn);  //done
	static  CardSuit CharToSuit(char inn);					//done
};
static Card CardDeck[]={ Card(0),
				  Card(1),Card(2),Card(3),Card(4),
				  Card(5),Card(6),Card(7),Card(8),
				  Card(9),Card(10),Card(11),Card(12),
				  Card(13),Card(14),Card(15),Card(16),
				  Card(17),Card(18),Card(19),Card(20),
				  Card(21),Card(22),Card(23),Card(24),
				  Card(25),Card(26),Card(27),Card(28),
				  Card(29),Card(30),Card(31),Card(32),
				  Card(33),Card(34),Card(35),Card(36),
				  Card(37),Card(38),Card(39),Card(40),
				  Card(41),Card(42),Card(43),Card(44),
				  Card(45),Card(46),Card(47),Card(48),
				  Card(49),Card(50),Card(51),Card(52)
};
Card  GetCard(byte value,CardSuit suit);
Card  GetCard(string inn);
void copy_2d_arr(Card dst[][21] ,const Card src[][21]);
bool CompareCardArr(const Card thes[][21],const Card src[][21]);
inline int  mmin(int i,int j)   //return minimal element of i and j;
{
	return ((i<=j) ? i : j);
}
#endif
