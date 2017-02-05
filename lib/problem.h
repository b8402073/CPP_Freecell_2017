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
	int  SearchBuffer(Card that) const;   //done,找不到傳回(-1)
	byte GetBufferSize() const;			  //done
	Card PeekBuffer(int pos) const;			//done pos in [0,3]
	Card    PeekCard(int col,int row) const; //done	
	Problem();								//done  "empty Problem Object" is equal to the "Problem of Complete World"
	Problem(const Card arr[][21],const byte anotherNowMaxPos[],const Buffer& mb);  //應該問題不大
	inline Problem* copy() const;			//done
	Problem(unsigned int Number);			//應該問題不大
	Problem(const Card arr[][21], const Buffer& mb); //done
	Problem(const Buffer& mb);
	Problem(const Problem& inn);			//easy
	~Problem();								//easy  因為沒有new,所以不必delete
	static bool Rule(Card upper,Card lower) ; //done (改成static比較好用)
	Card Peek(int srcLine) const;			//done  srcLine in [1,8]
	Card Fetch(int srcLine);				//應該問題不大
	Card FetchBuffer(Card that);			//應該問題不大
	bool Put(Card that,byte dstLine);		//應該問題不大
	bool PutBuffer(Card that);				//應該問題不大
	bool Pop(int srcLine);					//應該問題不大
	bool Down(Card that,int dstLine);		//應該問題不大
	inline byte Available() const { return MB.Available()+ HowManyBlankLines(); }
	Card CARDFUNCTION(Card thatcard,int delta) const; //應該問題不大
	int  WhereIs(Card thatcard) const;		//應該問題不大
    Card AHead(Card that) const;			//應該問題不大
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
	byte SortOf_NowMaxPos(int Line) const; //輸入1是最小值,輸入8是最大值 //eleglantly done
	string str() const;						//應該問題不大
	string str9() const;					//應該問題不大
	bool equals(const Problem* that) const; //done
	//void Normalize();						//不做這個函式,相關的功能改成class NP
	byte QuickWhereIs(Card that) const;		//done
	Finisher Synthesize_Finisher() const;	//done

	bool IsValid() const;					//應該問題不大
	bool ValueEquals(const Problem* that) const; //done
	byte* getBytes() const;						 //done; 使用此函式用完的結果要手動刪除
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
