#include "problem.h"
#include "Finisher.h"
#include "HistoryItem.h"

#ifndef WORLD_H
#define WORLD_H

class World
{
//	friend class U;
public:   //protected:
	Problem P;
	Finisher F;
	vector<HistoryItem> History;
private:
	NP*     tmpNPItem;
public:
	inline void ReleaseNPItem() { if (!tmpNPItem) delete tmpNPItem; tmpNPItem=NULL; }
public:
	World();
	World(int i);
	World(const Problem& PP);
	World(const Problem& PP,const Finisher& FF);
	World(const Problem& PP,vector<HistoryItem> HH);
	World(const Problem& PP,const Finisher& FF,vector<HistoryItem> HH);
	World(const World& WW);
	~World();
	World* copy() const;
	Card PeekCard(int line,int srow) const;
	Card FinisherTop(CardSuit S) const;
protected:
	Problem* BeforeChange;
	vector<HistoryItem> bfChangeHistory;
protected:
	bool CheckFinish() const;
	void ReserveWorld();
	void ResumeWorld();
	void ResumeWorld(Problem* PP,vector<HistoryItem> HH);
	void ReleaseWorld();
private:
	bool MOVELINE(int srcLine,int dstLine);
public:
	bool MOVELINE(Card High,Card Low);
	bool equals(const World* that) const;
	bool ValueEquals(const World* that) const;
	bool CONNECT(Card Upper,Card Lower);
	bool FINISH(Card that);
	bool POP(Card that);
	bool _DOWN(Card that,int dstLine);
	bool DOWN(Card that);
	bool AutoSafeUp();
	bool ALLUP();
	bool isComplete() const;
	string HistoryToString(int inn,bool head) const;
	string str() const;
	string str(bool ShowHistory,bool ShowFinisher) const;
	bool isDead() const;
	static vector<Card> UserFinish(const World* inn);

	string GetBufStrings() const;
	string GetStrings(int LineNum);
////////////////////////////////////////以下是由CS版Gamer的部分轉移的共用函式

	static string Finisher_View(Card that,const Finisher& FF);
	static int    Finisher_Num(Card that,const Finisher& FF);
	static int    Total_Obstruction_AV(const World& that,bool debug);
	static int    Total_Obstruction_AV(const World& that);
	static bool   CardNum_TotalAV(const World& X, const World& Y);
};

bool SHistory_BetterWorld(const World& next,const World& prev);

#endif