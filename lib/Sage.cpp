#include "Sage.h"
int Sage::InitObsNum=0;
Sage::Sage(WorldExt inn)
:root(inn),isComplete(false)
{
	Selection=100;
	Sage::InitObsNum=World::Total_Obstruction_AV(inn);
	MakeStone4(root);
}
Sage::Sage(WorldExt inn,int Select)
:root(inn),Selection(Select),isComplete(false)
{
	MakeStone4(root);
}

void Sage::MakeStone4(WorldExt inn)
{
	if (inn.isComplete())
	{
		isComplete=true; 
		Answers.push_back(inn);
		return;
	}
	vector< vector<WorldExt>* > stack;
	vector<WorldExt>* NexLayer=new vector<WorldExt>();
	inn.makeChild(0,NexLayer,&Answers);
	stack.push_back(NexLayer);
	for (int i=1; i<4; i++)    //進行四層的MakeChild
	{
		NexLayer=new vector<WorldExt>();
		int sz= stack[ stack.size()-1]->size();
		for (int j=0; j<sz; j++)
		{
			WorldExt& target= stack[ stack.size()-1]->at(j);
			//cout<< target.str()<<endl;
			target.makeChild(i,NexLayer,&Answers);
		}

		//Debug Code
		//static char ttt[6];
		//Dump(*NexLayer,"Level"+string(_itoa(i,ttt,10))+".txt");

		Sort_and_RemoveDuplication( NexLayer);
		stack.push_back(NexLayer);		
		time_t t=time(NULL);
		printf("%s\r\n",ctime(&t));
	}
	Stone.insert(Stone.end(), NexLayer->begin(), NexLayer->end() );
	std::sort(Stone.begin(), Stone.end(), TotalAV_SpEdition);
	 //這裡很容易判斷錯誤而到底要不要對 stack[k]的element進行delete 的動作
	//2017/02/24的結論是"要!"
	//考慮  int* a=new int(1); int *b=new int(2); int *c=new int(3); vector<int>* v=new vector<int>();
	//v->push_back(*a); v->push_back(*b); v->push_back(*c);
	//最後需要delete a; delete b; delete c;delete v;
	/****************以上是錯誤的判斷***************/

	//但是2017/02/25判斷的結果是"不要",因為在makeChild1~makeChild5裡面都有自動delete that;指標

	for (int k=0; k< stack.size(); k++)  
	{
		delete (stack[k]);
	}
	if (Answers.size()>0)
		isComplete=true;
}

WorldExt Sage::RightFS(WorldExt inn)
{
	WorldExt Best=WorldExt::NoAnswer;
	if (Answers.size()>0) {
		std::sort(Answers.begin(), Answers.end(), GoodSolution);
		Answers.erase(Answers.begin()+1,Answers.end());
		Best= Answers[0];
	}
	Answers.clear();
	const int MaxHeight=150;
	vector<WorldExt>* NexLayer=new vector<WorldExt>();
	inn.makeChild(inn.History.size(),NexLayer,&Answers);	
	for (int x=inn.History.size()+1; x<MaxHeight; x++)
	{
		cout<<"x="<<x<<" ";
		//cout<<endl<< NexLayer->at(0).str()<<endl;
		//cout<<"AnsSize="<<Answers.size()<<endl;
		if (NexLayer->size()>0)
		{
			if (!Best.equals(&WorldExt::NoAnswer))
			{
				if (NexLayer->at(0).History.size() +NexLayer->at(0).P.CardNum() > Best.History.size() )
				{
					//這一群解不用找了
					delete NexLayer;
					return WorldExt::NoAnswer;
				}
			}
			vector<WorldExt>* old=NexLayer;  //old should wait to die..
			NexLayer=new vector<WorldExt>();
			for (int k=0; k< mmin(Selection,old->size()); k++)
			{
				WorldExt& target=(old->at(k));
				target.makeChild(x,NexLayer,&Answers);
			}
			delete old;
			Sort_and_RemoveDuplication(NexLayer);
			if (Answers.size() >= 1)
			{
				std::sort(Answers.begin(), Answers.end(), GoodSolution);
				//old if (!Answers[0].equals(&Best))
				if (!EqualHistoryVector(Answers[0].History, Best.History))
				{
					if (!Best.equals(&WorldExt::NoAnswer))
					{
						if (BetterHistoryArbitary(Answers[0].History, Best.History))
						{
							Answers.erase(Answers.begin()+1,Answers.end());
							Best=Answers[0];							
						}
					}else
					{
						Best=Answers[0];
					}
					delete NexLayer;
					return Best;
				}
			}
			if (NexLayer->size()>0)
			{
				continue;
			}else {
				delete NexLayer;
				return WorldExt::NoAnswer;
			}
		}else {
			delete NexLayer;
			return WorldExt::NoAnswer;
		}
	}
	delete NexLayer;
	return WorldExt::NoAnswer;
}


/***
 * 隨便找一個解
 */
bool Sage::Run1(bool prt_debug)  
{
	if (Answers.size()>0) {
		std::sort(Answers.begin(), Answers.end(), GoodSolution);
		Result=Answers[0];
		return true;
	}
	int sz=Stone.size();
	for (int i=0; i<sz; i++)
	{
		Cur_Pos=i;
		if (prt_debug)
		{
			cout<< Cur_Pos <<"/" << sz<<"\t\t\t";
			time_t t=time(NULL);
			printf("%s\r\n",ctime(&t));
		}

		WorldExt hand= RightFS(Stone[i]);
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
		if (!hand.equals(&WorldExt::NoAnswer))
		{
			if (Result.History.size()==0) 
			{
				Result=hand;
			}
			else if (BetterHistoryArbitary(hand.History, Result.History))
			{
				Result=hand;
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
	Answers.clear();
	if (Result.History.size()>0)
		Answers.push_back(Result);
	
	WorldExt hand=RightFS(Stone[X]);
	if (!hand.equals(&WorldExt::NoAnswer)) {
		//Result=hand;
		return hand;
	}
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
bool TotalAV_SpEdition(const World& X,const World& Y)
{
	int x0= World::Total_Obstruction_AV(X);
	int y0= World::Total_Obstruction_AV(Y);
	const bool WHEN_WE_DONT_CARE=false;
	int x1,y1;
	if (x0>= Sage::InitObsNum/2 && y0>=Sage::InitObsNum/2)
	{
		x1= X.P.CardNum()-X.P.Available();
		y1= Y.P.CardNum()-Y.P.Available();
	}else
	{
		x1= X.P.CardNum();
		y1= Y.P.CardNum();
	}
	if (x1<y1)
		return true;
	else if (x1>y1)
		return false;
	else
	{
		int x2= World::Total_Obstruction_AV(X);
		int y2= World::Total_Obstruction_AV(Y);
		if (x2< Sage::InitObsNum/2 && y2<Sage::InitObsNum)
			goto Level5;
		if (x2<y2)
			return true;
		else if (x2>y2)
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
				int x4=X.P.CardNum();
				int y4=Y.P.CardNum();
				if (x4<y4)
					return true;
				else if (x4>y4)
					return false;
				else
				{
Level5:
					int x5=X.P.MaxOf_NowMaxPos();
					int y5=Y.P.MaxOf_NowMaxPos();
					if (x5<y5)
						return true;
					else if (x5>y5)
						return false;
					else
					{
						string x6=X.P.str();
						string y6=Y.P.str();
						if (x6<y6)
							return true;
						else if (x6>y6)
							return false;
						else
						{
							if (BetterHistoryEqualSize(X.History,Y.History))
								return true;
							else 
								return false;  //因為WHEN_WE_DONT_CARE也傳回false							
						}
					}
				}
			}
		}
	}
	assert(false);
	return WHEN_WE_DONT_CARE;
}
void Sage::Sort_and_RemoveDuplication(vector<WorldExt>* inn)  //包含有sort的動作
{
	std::sort(inn->begin(), inn->end(), TotalAV_SpEdition);
	std::unique(inn->begin(), inn->end(), EqualWorldExt);
}
bool GoodSolution(const WorldExt& X,const WorldExt& Y)
{
	assert(X.P.equals(&(Y.P)));
	return BetterHistoryArbitary(X.History, Y.History);
}