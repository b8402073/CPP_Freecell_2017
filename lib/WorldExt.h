#include <fstream>
#include "World.h"

/*
	�M���@�Ѫ��Ҳ�,�w�g���\�]�F
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
	//�W������
	//L1a :  �K�i�P�i�HPeek���P
	//L1b :  Cell(�κ�Buffer)���P
	bool makeChild0(int Level);  //MOVELINE
	bool makeChild1(int Level);  //CONNECT(8,8)
	bool makeChild2(int Level);  //CONNECT(8,Cell)
	bool makeChild3AB(int Level);//FINISH
	bool makeChild4(int Level);  //DOWN(L1a)+DOWN(L1b)
	bool makeChild5(int Level);  //POP(L1a)
public:
	//bool POP_N(int Line,int N);//�̾�2017/01/31�]�p�M�w�R��

	//�H�U�禡�򥻤W�O��World���ʧ@�A���O�[�W����Ping-Pong�������{���X
public:
	bool POP(Card that);
	bool MOVELINE(Card High,Card Low);
	bool CONNECT(Card Upper,Card Lower);
	//bool FINISH(Card that);   //���|��Ping-Pong����
	bool DOWN(Card that);
	static WorldExt NoAnswer;
	//static vector<WorldExt*> Garbage[150];
};

//static vector<WorldExt*> Garbage[150];

/***
 * NoAnswer�O�@�ӯS�O���ܼ�,�t�XSage::RightFS�ϥ�;
 * �o�ӪF�誺�]�p���I�b��NoAnswer.P.CardNum()!=0, �ҥHNoAnswer.isComplete()==false
 */
/* old
static WorldExt  NoAnswer(Problem(Buffer(_NO_ANSWER_MB)), 
						  Finisher(_Empty,_Empty,_Empty,_Empty),
						  vector<HistoryItem>(0) );
*/







void Dump(const vector<WorldExt>& vec,string filename);
bool TotalAV(const World& X,const World& Y);

#endif