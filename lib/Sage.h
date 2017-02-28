#include <ctime>
#include "WorldExt.h"
#ifndef SAGE_H
#define SAGE_H

class Sage
{
public:
	const WorldExt root;
	WorldExt Result;
	int Total_Work;
	int Cur_Pos;
	int Selection;
	static int InitObsNum;
	bool isComplete;

	Sage(WorldExt inn);
	Sage(WorldExt inn,int Select);
	bool Run1(bool prt_debug);   //隨便找一個解
	bool Run2(bool prt_debug);   //找一個比較好的解,依賴RunX
	WorldExt RunX(bool prt_debug,int X);

	vector<WorldExt> Stone;
	vector<WorldExt> Answers;

public:
	void MakeStone4(WorldExt inn);
private:
	WorldExt RightFS(WorldExt inn);
	void Sort_and_RemoveDuplication(vector<WorldExt>* inn);
};
bool TotalAV_SpEdition(const World& X,const World& Y);
bool TotalAV(const World& X,const World& Y);
inline bool EqualWorldExt(const WorldExt& X,const WorldExt& Y){ return X.ValueEquals(&Y); }
bool GoodSolution(const WorldExt& X, const WorldExt& Y);
#endif