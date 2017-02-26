#include <fstream>
#include "World.h"

/*
	尋找單一解的模組,已經成功跑了
*/


#ifndef WORLDEXT_H
#define WORLDEXT_H

static Card _NO_ANSWER_MB[4]= { Card(_EndOfStream),Card(_EndOfStream),Card(_EndOfStream),Card(_EndOfStream)};



class WorldExt : public World     
{
public:	
	vector<WorldExt>* MyChild;
	vector<WorldExt>* MyCompleteAnswer;
	WorldExt(const Problem& PP);
	WorldExt(const Problem& PP,const vector<HistoryItem>& HH);
	WorldExt(const Problem& PP,const Finisher& FF,const vector<HistoryItem>& HH);
	WorldExt(const WorldExt& WE);
	WorldExt();
	WorldExt* copy() const;
	bool ChildRoutine(bool flag,WorldExt* that,int Level);
	void makeChild(int Level,vector<WorldExt>* ptrChild, vector<WorldExt>* ptrCompleteAnswer);
private:
	//名詞解釋
	//L1a :  八張牌可以Peek的牌
	//L1b :  Cell(或稱Buffer)的牌
	bool makeChild0(int Level);  //MOVELINE
	bool makeChild1(int Level);  //CONNECT(8,8)
	bool makeChild2(int Level);  //CONNECT(8,Cell)
	bool makeChild3AB(int Level);//FINISH
	bool makeChild4(int Level);  //DOWN(L1a)+DOWN(L1b)
	bool makeChild5(int Level);  //POP(L1a)
public:
	//bool POP_N(int Line,int N);//依據2017/01/31設計決定刪除

	//以下函式基本上是做World的動作，但是加上防止Ping-Pong效應的程式碼
public:
	bool POP(Card that);
	bool MOVELINE(Card High,Card Low);
	bool CONNECT(Card Upper,Card Lower);
	//bool FINISH(Card that);   //不會有Ping-Pong效應
	bool DOWN(Card that);
	static WorldExt NoAnswer;
	//static vector<WorldExt*> Garbage[150];
};

//static vector<WorldExt*> Garbage[150];

/***
 * NoAnswer是一個特別的變數,配合Sage::RightFS使用;
 * 這個東西的設計重點在於NoAnswer.P.CardNum()!=0, 所以NoAnswer.isComplete()==false
 */
/* old
static WorldExt  NoAnswer(Problem(Buffer(_NO_ANSWER_MB)), 
						  Finisher(_Empty,_Empty,_Empty,_Empty),
						  vector<HistoryItem>(0) );
*/







void Dump(const vector<WorldExt>& vec,string filename);
bool TotalAV(const World& X,const World& Y);

#endif