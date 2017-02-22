#include "Sage.h"
Sage::Sage(WorldExt inn)
:root(inn),isComplete(false)
{
	Selection=100;
	UOne.Clear();
	MakeStone4(root);
}
Sage::Sage(WorldExt inn,int Select)
:root(inn),Selection(Select),isComplete(false)
{
	UOne.Clear();
	MakeStone4(root);
}

/*
void Sage::MakeStone(WorldExt inn)
{
	if (inn.isComplete())
	{
		isComplete=true;
		return;
	}
	vector<WorldExt> C1= inn.makeChild(0,100,"");
	vector<WorldExt> C2;
	for (int i=0; i<C1.size(); i++)
	{
		if (C1[i].isComplete())
		{
			Result=C1[i];
			isComplete=true;
			return;
		}else if (C1[i].isDead())
			continue;
		else
		{
			C1[i].makeChild(0,100,"");
			C2.insert(C2.end(),C1[i].Child.begin(), C1[i].Child.end());
		}
	}
	std::sort(C2.begin(), C2.end(), TotalAV);
									
	for (int i=0; i<C2.size(); i++)
	{
		if (C2[i].isComplete())
		{
			Result=C2[i];
			isComplete=true;
			return;
		}else if (C2[i].isDead())
			continue;
		else
		{
			C2[i].makeChild(0,100,"");
			Stone.insert(Stone.end(), C2[i].Child.begin(), C2[i].Child.end());
		}
	}
	std::sort(Stone.begin(), Stone.end(), TotalAV);
}

*/

void Sage::MakeStone4(WorldExt inn)
{
	if (inn.isComplete())
	{
		isComplete=true; return;
	}
	vector<WorldExt> hand= inn.makeChild(0,100,"");
	vector< vector<WorldExt>* > stack;
	vector<WorldExt>* NexLayer;
	for (int i=1; i<4; i++)    //進行四層的MakeChild
	{
		NexLayer=new vector<WorldExt>();
		int sz= (i==1) ? hand.size() : stack[ stack.size()-1]->size();
		for (int j=0; j<sz; j++)
		{
			if (i==1)
			{
				vector<WorldExt> tmp= hand[j].makeChild(0,100,"");
				std::sort(tmp.begin(), tmp.end(), TotalAV);
				NexLayer->insert(NexLayer->end(), tmp.begin(), tmp.end());
			}else
			{
				vector<WorldExt>* targetBuffer= stack[ stack.size()-1 ];
				vector<WorldExt> tmp= targetBuffer->at(j).makeChild(0,100,"");
				std::sort(tmp.begin(), tmp.end(), TotalAV);
				NexLayer->insert(NexLayer->end(), tmp.begin(), tmp.end());
			}
		}
		stack.push_back(NexLayer);		
	}
	Stone.insert(Stone.end(), NexLayer->begin(), NexLayer->end() );
	std::sort(Stone.begin(), Stone.end(), TotalAV);
	for (int k=0; k< stack.size(); k++)
	{
		delete (stack[k]);
	}
}
WorldExt Sage::RightFS(std::vector<WorldExt> inn)
{
	const int MaxHeight=150;
	for (int x=0; x<=MaxHeight; x++)
	{
		//cout<<"Best(x="<<x<<"):"<<endl;
		//cout<< inn[0].str()<<endl;
		if (inn.size()>0)
		{
			if (Result.History.size()>0)
			{
				if (inn[0].History.size() +inn[0].P.CardNum() > Result.History.size() )
				{
					//這一群解不用找了
					return WorldExt::NoAnswer;
				}
			}

			if (inn[0].isComplete())
			{
				isComplete=true;
				return inn[0];
			}else if (isComplete)
			{
				return WorldExt::NoAnswer;
			}
			vector<WorldExt> NexLayer;
			for (int k=0; k< mmin(Selection,inn.size()); k++)
			{
				inn[k].makeChild(x,100,"");
				//Insert All elements in inn[k].Child into NexLayer
				NexLayer.insert(NexLayer.end(),inn[k].Child.begin(), inn[k].Child.end());
			}
			std::sort(NexLayer.begin(), NexLayer.end(),TotalAV);
			if (NexLayer.size()>0)
			{
				inn.clear();
				//std::copy(NexLayer.begin(), NexLayer.end(), inn.begin());
				inn.insert(inn.end(), NexLayer.begin(), NexLayer.end() );
			}else
				return WorldExt::NoAnswer;
		}else
			return WorldExt::NoAnswer;
	}
	return WorldExt::NoAnswer;
}
/***
 * 隨便找一個解
 */
bool Sage::Run1(bool prt_debug)  
{
	if (isComplete)
		return true;
	int sz=Stone.size();
	for (int i=0; i<sz; i++)
	{
		Cur_Pos=i;
		if (prt_debug)
		{
			cout<< Cur_Pos <<"/" << sz<<"\t\t\t"<<"time"<<endl;
		}
		vector<WorldExt> LS;
		LS.push_back(Stone[i]);
		WorldExt hand= RightFS(LS);
		if (hand.isComplete())
		{
			Result=hand;
			return true;
		}
	}
	isComplete=true;
 	return false;
}
/***
 *  找一個合理較佳解
 */
bool Sage::Run2(bool prt_debug)
{
	if (isComplete)
		return true	;
	for (int i=0; i<Stone.size(); i++)
	{
		Cur_Pos=i;
		if (prt_debug)
		{
			cout<< Cur_Pos <<"/" << Stone.size()<<"\t\t\t";
			time_t t=time(NULL);
			printf("%s\r\n",ctime(&t));
		}
		WorldExt hand=RunX(prt_debug,i);
		isComplete=false;
		if (hand.isComplete())
		{
			if (Result.History.size()==0)
			{
				Result=hand;
			}else
			{
				if (BetterHistoryArbitary(hand.History, Result.History))
				{
					Result=hand;
				}
			}
		}
		cout<<Result.str()<<endl;
	}
	if (Result.History.size()>0)
		return true;
	return false;
}
WorldExt Sage::RunX(bool prt_debug,int X)
{
	if (isComplete)
		return true;
	int sz=Stone.size();
	assert(X>=0 && X<sz);	
	vector<WorldExt> LS;
	LS.push_back(Stone[X]);
	WorldExt hand=RightFS(LS);
	if (hand.isComplete())
		return hand;
	isComplete=true;
	return WorldExt::NoAnswer;
}
bool TotalAV(const World& X,const World& Y)
{
	const bool WHEN_WE_DONT_CARE=false;
	int x2= World::Total_Obstruction_AV(X);
	int y2= World::Total_Obstruction_AV(Y);
	if (x2<y2)
		return true;
	else if (x2>y2)
		return false;
	else
	{
		int x1= X.P.CardNum()-X.P.Available();
		int y1= Y.P.CardNum()-Y.P.Available();
		if (x1<y1)
			return true;
		else if (x1>y1)
			return false;
		else
		{
			int x3= X.P.Available();
			int y3= Y.P.Available();
			if (x3>y3)
				return true;
			else if (x3<y3)
				return false;
			else
			{
				int x4=X.P.MaxOf_NowMaxPos();
				int y4=Y.P.MaxOf_NowMaxPos();
				if (x4<y4)
					return true;
				else if (x4>y4)
					return false;
				else
					return WHEN_WE_DONT_CARE;
			}
		}
	}
	assert(false);
	return WHEN_WE_DONT_CARE;
}