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
	bool isComplete;

	Sage(WorldExt inn);
	Sage(WorldExt inn,int Select);
	bool Run1(bool prt_debug);   //�H�K��@�Ӹ�
	bool Run2(bool prt_debug);   //��@�Ӥ���n����,�̿�RunX
	WorldExt RunX(bool prt_debug,int X);

	vector<WorldExt> Stone;
	vector<WorldExt> Answers;
public:
	//void MakeStone(WorldExt inn);
	void MakeStone4(WorldExt inn);
private:
//	WorldExt RightFS(vector<WorldExt> inn);
};

#endif