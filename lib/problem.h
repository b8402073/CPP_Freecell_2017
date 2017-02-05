#include "Buffer.h"
#include "Finisher.h"


#ifndef PROBLEM_H
#define PROBLEM_H 
class NP;
class Problem 
{
private:
	Card cardarr[8][21];
	byte NowMaxPos[8];	
	Buffer MB;
	void Upd_NowMaxPos();
	byte Synthesize(CardSuit S) const;

public:
	byte GetNowMaxPos(byte Line) const;	  //done
	vector<Card>  BufferToVector() const; //done
	int  SearchBuffer(Card that) const;   //done,�䤣��Ǧ^(-1)
	byte GetBufferSize() const;			  //done
	Card PeekBuffer(int pos) const;			//done pos in [0,3]
	Card    PeekCard(int col,int row) const; //done	
	Problem();								//done  "empty Problem Object" is equal to the "Problem of Complete World"
	Problem(const Card arr[][21],const byte anotherNowMaxPos[],const Buffer& mb);  //���Ӱ��D���j
	inline Problem* copy() const;			//done
	Problem(unsigned int Number);			//���Ӱ��D���j
	Problem(const Card arr[][21], const Buffer& mb); //done
	Problem(const Buffer& mb);
	Problem(const Problem& inn);			//easy
	~Problem();								//easy  �]���S��new,�ҥH����delete
	static bool Rule(Card upper,Card lower) ; //done (�令static����n��)
	Card Peek(int srcLine) const;			//done  srcLine in [1,8]
	Card Fetch(int srcLine);				//���Ӱ��D���j
	Card FetchBuffer(Card that);			//���Ӱ��D���j
	bool Put(Card that,byte dstLine);		//���Ӱ��D���j
	bool PutBuffer(Card that);				//���Ӱ��D���j
	bool Pop(int srcLine);					//���Ӱ��D���j
	bool Down(Card that,int dstLine);		//���Ӱ��D���j
	inline byte Available() const { return MB.Available()+ HowManyBlankLines(); }
	Card CARDFUNCTION(Card thatcard,int delta) const; //���Ӱ��D���j
	int  WhereIs(Card thatcard) const;		//���Ӱ��D���j
    Card AHead(Card that) const;			//���Ӱ��D���j
	int  CardNum() const;					//done
	byte POSITION(Card thatcard) const;		//done
	byte POSITION(Card thatcard,int srcLine) const; //done
	vector<byte> BlankLine() const;			//done
	vector<byte> OneCardLine() const;		//done
	int  FirstBlankLine() const;			//done  ret in [1,8]
	int  HowManyBlankLines() const;			//done  
	int  HowManyOneCardLines() const;		//done
	int  OneCardSum() const;				//done
	byte MaxOf_NowMaxPos() const;			//done
	byte SecondOf_NowMaxPos() const;		//elegantly done
	byte SortOf_NowMaxPos(int Line) const; //��J1�O�̤p��,��J8�O�̤j�� //eleglantly done
	string str() const;						//���Ӱ��D���j
	string str9() const;					//���Ӱ��D���j
	bool equals(const Problem* that) const; //done
	//void Normalize();						//�����o�Ө禡,�������\��令class NP
	byte QuickWhereIs(Card that) const;		//done
	Finisher Synthesize_Finisher() const;	//done

	bool IsValid() const;					//���Ӱ��D���j
	bool ValueEquals(const Problem* that) const; //done
	byte* getBytes() const;						 //done; �ϥΦ��禡�Χ������G�n��ʧR��
	const Buffer& GetBuffer() const { return MB;}//done
};
vector<Card> _GetDragon(const Problem& P,int srcLine);
vector<Card> GetDragonDestNotNull(const Problem& P,int srcLine,Card cut);
vector<Card> GetDragonDestIsNull(const  Problem& P,int srcLine);

class NP
{
public:
	byte NormLineOrder[8];  
	Problem Input,OutputArr;
	NP(const Problem& inn);   //done
	void Normalize();			//done
	vector<Card> getVector();	  //done
	string str();
	static byte*   VectorToBytes(vector<Card> that);  //done
	static Problem BytesToProblem(const byte* ptr);		//
	static void    PrintVector( vector<Card> that);   //done
};



#endif
