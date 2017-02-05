#define WE_NEED_UONE
/*
	尋找單一解的模組,已經成功跑了
*/

#include "World.h"

#ifndef WORLDEXT_H
#define WORLDEXT_H

class WorldExt;

/*
這些移到World裡面當static method
string  Finisher_View(Card that,const Finisher& FF);
int  Finisher_Num(Card that,const Finisher& FF);
int  Total_Obstruction_AV(const WorldExt& that,bool debug);
bool CardNum_TotalAV(const World& prev,const World& next);
*/

class U
{
private:
	vector<WorldExt> Data[22][22][5];
public:
	U();
private:
	bool SubExist(const vector<WorldExt>& V,const WorldExt& that) const;
public:
	int WorldNum() const;
	int WorldMax() const;
	void Clear();
	bool Add(WorldExt that);
	bool Exist(WorldExt that) const; 
	bool Remove(WorldExt that);
	WorldExt* EE(WorldExt inn);  ////'輸入一個局,如果成功找到已經儲存過的局，把那個局傳回來，如果找不到傳回Null
	int Locate(WorldExt that) const;	
};
#ifdef  WE_NEED_UONE
static U  UOne;  //這是一個全域變數
#endif

static Card _NO_ANSWER_MB[4]= { Card(_EndOfStream),Card(_EndOfStream),Card(_EndOfStream),Card(_EndOfStream)};


class WorldExt : public World     
{
public:	
	vector<WorldExt> Child;
	WorldExt(const Problem& PP);
	WorldExt(const Problem& PP,const vector<HistoryItem>& HH);
	WorldExt(const Problem& PP,const Finisher& FF,const vector<HistoryItem>& HH);
	WorldExt(const WorldExt& WE);
	WorldExt();
	WorldExt* copy() const;
	bool ChildRoutine(bool flag,WorldExt* that,int Level,int HiLevel);
	vector<WorldExt>& makeChild(int Level,int HiLevel,string Prefix);
private:
	//名詞解釋
	//L1a :  八張牌可以Peek的牌
	//L1b :  Cell(或稱Buffer)的牌
	bool makeChild0(int Level,int HiLevel);  //MOVELINE
	bool makeChild1(int Level,int HiLevel);  //CONNECT(8,8)
	bool makeChild2(int Level,int HiLevel);  //CONNECT(8,Cell)
	bool makeChild3AB(int Level,int HiLevel);//FINISH
	bool makeChild4(int Level,int HiLevel);  //DOWN(L1a)+DOWN(L1b)
	bool makeChild5(int Level,int HiLevel);  //POP(L1a)
public:
	//bool POP_N(int Line,int N);//依據2017/01/31設計決定刪除

	//以下函式基本上是做World的動作，但是加上防止Ping-Pong效應的程式碼
public:
	bool POP(Card that);
	bool MOVELINE(Card High,Card Low);
	bool CONNECT(Card Upper,Card Lower);
	//bool FINISH(Card that);
	bool DOWN(Card that);
};
/***
 * NoAnswer是一個特別的變數,配合Sage::RightFS使用;
 * 這個東西的設計重點在於NoAnswer.P.CardNum()!=0, 所以NoAnswer.isComplete()==false
 */
static WorldExt  NoAnswer(Problem(Buffer(_NO_ANSWER_MB)), 
						  Finisher(_Empty,_Empty,_Empty,_Empty),
						  vector<HistoryItem>(0) );

class Sage
{
public:
	const WorldExt root;
	WorldExt Result;
	int Total_Work;
	int Cur_Pos;
	int Selection;
	bool isComplete;

	Sage(WorldExt inn);
	Sage(WorldExt inn,int Select);
	bool Run1(bool prt_debug);   //隨便找一個解
	bool Run2(bool prt_debug);   //找一個比較好的解,依賴RunX
	WorldExt RunX(bool prt_debug,int X);

	vector<WorldExt> Stone;
public:
	//void MakeStone(WorldExt inn);
	void MakeStone4(WorldExt inn);
private:
	WorldExt RightFS(vector<WorldExt> inn);
};


bool TotalAV(const World& X,const World& Y);

#endif