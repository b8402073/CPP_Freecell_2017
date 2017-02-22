#include "U.h"
#include "WorldExt.h"
WorldExt::WorldExt(const Problem &PP)
:World(PP){}


WorldExt::WorldExt(const Problem& PP,const vector<HistoryItem>& HH)
:World(PP,HH){}

WorldExt::WorldExt(const Problem& PP,const Finisher& FF, const vector<HistoryItem>& HH)
:World(PP,FF,HH){}

WorldExt::WorldExt(const WorldExt& WE)
:World(WE) {}

WorldExt::WorldExt()
:World(Problem(),Finisher(C13,D13,H13,S13) ){}


WorldExt* WorldExt::copy() const
{
	return new WorldExt(P,F,History);
}
bool WorldExt::ChildRoutine(bool flag, WorldExt* that, int Level, int HiLevel)
{
	//cout<< this->str()<<endl;    //code for debugging
	if (flag)
	{
		if (!that->isDead())
		{
			//要有快速解可以在這裡加that.AutoSafeUp();
			WorldExt* Copy=that->copy();
			Copy->ALLUP();
			if (Copy->isComplete())
			{
				that->ALLUP();				
			}
			delete Copy;
			if (that->isComplete())
			{
				Child.push_back(*that);
				return true;
			}else if (Level>=HiLevel)
			{
				Child.push_back(*that);
				return false;
			}else if (!UOne.Exist(*that))
			{	
				UOne.Add(*that);
				Child.push_back(*that);
				return false;
			}else
			{
				//如果UOne已經存在that
				WorldExt* hand=UOne.EE(*that);
				const vector<HistoryItem>& Old= hand->History;
				const vector<HistoryItem>& nnew=that->History;
				if (BetterHistoryArbitary(nnew,Old))
				{
					hand->History.clear();
					hand->History.insert(hand->History.end(), nnew.begin(), nnew.end() );					
					Child.push_back(*that);
				}
				return false;
			}
		}
	}
	return false;
}

vector<WorldExt>& WorldExt::makeChild(int Level,int HiLevel,string Prefix)
{
	//cout<<endl<< this->P.str()<<endl;

	if (!makeChild0(Level,HiLevel))    //MOVELINE
	{
		if (!makeChild1(Level,HiLevel))  //CONNECT
		{
			if (!makeChild2(Level,HiLevel))//CONNECT(Cell,8)+DOWN(Cell)
			{
				if (!makeChild3AB(Level,HiLevel)) //FINISH
				{
					if (!makeChild4(Level,HiLevel))//DOWN(L1a)+DOWN(L1b)
					{
						makeChild5(Level,HiLevel); //POP(L1a)
					}					
				}
			}
		}
	}
	if (Prefix!="")
	{
		//Java Code
		//String FN="C:\\Tmp\\"+"J"+Prefix+"_"+Level+"_beforeSort.TXT";
        //Verify.WriteStringToText(FN, Verify.ListWorldToString(Child, true, true,true));
		cout<<"Hello"<<endl;
	}
	
	//@@?
	//std::sort(Child.begin(), Child.end(), CardNum_TotalAV);  //為求快速,所以暫時REM此行
	return Child;
}
bool WorldExt::makeChild0(int Level, int HiLevel)  //MOVELINE
{
	int i,j;
	for ( i=1; i<=8; i++)
	{
		for ( j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Card upper=this->P.Peek(i);
				Card lower=this->P.Peek(j);
				if (lower!=NULL && upper!=NULL &&
					lower.GetSuit()!=NONE &&
					upper.GetSuit()!=NONE)
				{
					WorldExt* that=(this->copy());
					if (!ChildRoutine(that->MOVELINE(upper,lower),that,Level,HiLevel))
					{
						delete that;
						continue;
					}
					else
					{
						delete that;
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool WorldExt::makeChild1(int Level, int HiLevel)  //CONNECT(8,8)
{
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Card upper=P.Peek(i);
				Card lower=P.Peek(j);
				if (lower!=NULL && upper!=NULL &&
					lower!=NONE && upper!=NONE)
				{
					if (Problem::Rule(upper,lower))
					{
						WorldExt* that= this->copy();
						if (!ChildRoutine(that->CONNECT(upper,lower),that,Level,HiLevel))
						{
							delete that;
							continue;
						}else
						{
							delete that;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
bool WorldExt::makeChild2(int Level,int HiLevel)  //CONNECT(Cell,8)+DOWN(Cell)
{	
	vector<Card> B= P.GetBuffer().toVector();
	for (int i=0; i<B.size(); i++)
	{
		Card lower=B[i];
		for (int j=1; j<=8; j++)
		{
			Card upper=P.Peek(j);
			if (upper!=_Empty)
			{
				if (Problem::Rule(upper,lower))
				{
					WorldExt* that=this->copy();
					if (!ChildRoutine(that->CONNECT(upper,lower),that,Level,HiLevel))
					{
						delete that;
						continue;
					}else
					{
						delete that;
						return true;
					}
				}
			}else
			{
				WorldExt* that=this->copy();
				if (!ChildRoutine(that->DOWN(lower),that,Level,HiLevel))
				{
					delete that;
					continue;
				}else
				{
					delete that;
					return true;
				}
			}
		}
	}
	return false;
}
bool WorldExt::makeChild3AB(int Level,int HiLevel)  //FINISH
{
	vector<Card> B=this->P.GetBuffer().toVector();
	for (int col=1; col<=8; col++)
	{
		Card hand=P.Peek(col);
		if (hand!=NULL)
		{
			B.push_back(hand);
		}
	}
	for (int i=0; i<B.size(); i++)
	{
		if (F.Needed(B[i]))
		{
			WorldExt* that=this->copy();
			if (!ChildRoutine(that->FINISH(B[i]),that,Level,HiLevel))
			{
				delete that;
				continue;
			}else
			{
				delete that;
				return true;
			}
		}
	}
	return false;
}	
bool WorldExt::makeChild4(int Level, int HiLevel)  //DOWN(L1a)+DOWN(L1b)
{
	int dstLine=P.FirstBlankLine();
	if (dstLine>0)
	{
		vector<Card> B;		
		for (int col=1; col<=8; col++)
		{
			Card hand=P.Peek(col);
			if (hand!=NULL)
			{
				B.push_back(hand);
			}
		}
		for (int i=0; i<P.GetBufferSize(); i++)
		{
			B.push_back(P.PeekBuffer(i));
		}
		for (int i=0; i<B.size(); i++)
		{
			WorldExt* that=this->copy();
			if (!ChildRoutine(that->DOWN(B[i]), that,Level,HiLevel))
			{
				delete that;
				continue;
			}
			else
			{
				delete that;
				return true;
			}
		}
	}
	return false;
}
bool WorldExt::makeChild5(int Level, int HiLevel)  //POP(L1a)
{
	if (P.Available()>0)
	{
		for (int i=1; i<=8; i++)
		{
			Card Hand=P.Peek(i);
			if (Hand!=NULL)
			{
				WorldExt* that=this->copy();
				if (!ChildRoutine(that->POP(Hand),that,Level,HiLevel))
				{
					delete that;
					continue;
				}else
				{
					delete that;
					return true;
				}					
			}
		}
	}
	return false;
}
bool WorldExt::POP(Card that)
{
	//參考History的資料消除可能發生的Ping-Pong現象
	if (History.size()>1 )
	{
		HistoryItem Last= History[ History.size()-1 ];
		if (Last.Action==ACTION_TYPE::DOWN && Last.Card1==that) 
			return false;
	}
	return World::POP(that);
}
bool WorldExt::DOWN(Card that)
{
	if (History.size()>=1)
	{
		HistoryItem Last=History[ History.size()-1 ];
		if (Last.Action==ACTION_TYPE::POP && Last.Card1== that)
			return false;
	}
	return World::DOWN(that);
}
bool WorldExt::MOVELINE(Card High,Card Low)
{
	if (History.size()>2)
	{
		HistoryItem LastEx2=History[ History.size()-2 ];
		HistoryItem Last=History[ History.size()-1 ];
		if (Last.Action==ACTION_TYPE::MOVELINE && 
			LastEx2.Action==ACTION_TYPE::MOVELINE &&
			Last.Card2==Low && LastEx2.Card2==Low && LastEx2.Card1==High)
		{
			//到這裡就確定有Ping-Pong出現了,要阻止
			return false;
		}
	}
	return World::MOVELINE(High,Low);
}

bool WorldExt::CONNECT(Card Upper,Card Lower)
{
	if (History.size()>2)
	{
		HistoryItem LastEx2=History[ History.size()-2 ];
		HistoryItem Last=History[ History.size()-1 ];
		if (Last.Action==ACTION_TYPE::CONNECT &&
			LastEx2.Action==ACTION_TYPE::CONNECT &&
			Last.Card2==Lower && LastEx2.Card2==Lower && LastEx2.Card1==Upper)
		{
			return false;
		}
	}
	return World::CONNECT(Upper,Lower);
}

