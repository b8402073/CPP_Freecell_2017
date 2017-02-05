#define WE_NEED_UONE
/*
	�M���@�Ѫ��Ҳ�,�w�g���\�]�F
*/

#include "World.h"

#ifndef WORLDEXT_H
#define WORLDEXT_H

class WorldExt;

/*
�o�ǲ���World�̭���static method
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
	WorldExt* EE(WorldExt inn);  ////'��J�@�ӧ�,�p�G���\���w�g�x�s�L�����A�⨺�ӧ��Ǧ^�ӡA�p�G�䤣��Ǧ^Null
	int Locate(WorldExt that) const;	
};
#ifdef  WE_NEED_UONE
static U  UOne;  //�o�O�@�ӥ����ܼ�
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
	//�W������
	//L1a :  �K�i�P�i�HPeek���P
	//L1b :  Cell(�κ�Buffer)���P
	bool makeChild0(int Level,int HiLevel);  //MOVELINE
	bool makeChild1(int Level,int HiLevel);  //CONNECT(8,8)
	bool makeChild2(int Level,int HiLevel);  //CONNECT(8,Cell)
	bool makeChild3AB(int Level,int HiLevel);//FINISH
	bool makeChild4(int Level,int HiLevel);  //DOWN(L1a)+DOWN(L1b)
	bool makeChild5(int Level,int HiLevel);  //POP(L1a)
public:
	//bool POP_N(int Line,int N);//�̾�2017/01/31�]�p�M�w�R��

	//�H�U�禡�򥻤W�O��World���ʧ@�A���O�[�W����Ping-Pong�������{���X
public:
	bool POP(Card that);
	bool MOVELINE(Card High,Card Low);
	bool CONNECT(Card Upper,Card Lower);
	//bool FINISH(Card that);
	bool DOWN(Card that);
};
/***
 * NoAnswer�O�@�ӯS�O���ܼ�,�t�XSage::RightFS�ϥ�;
 * �o�ӪF�誺�]�p���I�b��NoAnswer.P.CardNum()!=0, �ҥHNoAnswer.isComplete()==false
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
	bool Run1(bool prt_debug);   //�H�K��@�Ӹ�
	bool Run2(bool prt_debug);   //��@�Ӥ���n����,�̿�RunX
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