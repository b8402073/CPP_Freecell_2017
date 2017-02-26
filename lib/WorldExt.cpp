
#include "WorldExt.h"
//vector<WorldExt*> WorldExt::Garbage[150];

WorldExt WorldExt::NoAnswer=WorldExt(Problem(Buffer(_NO_ANSWER_MB)), 
						  Finisher(_Empty,_Empty,_Empty,_Empty),
						  vector<HistoryItem>(0) );

WorldExt::WorldExt(const Problem &PP)
:World(PP),MyChild(NULL),MyCompleteAnswer(NULL){}


WorldExt::WorldExt(const Problem& PP,const vector<HistoryItem>& HH)
:World(PP,HH),MyChild(NULL),MyCompleteAnswer(NULL){}

WorldExt::WorldExt(const Problem& PP,const Finisher& FF, const vector<HistoryItem>& HH)
:World(PP,FF,HH),MyChild(NULL),MyCompleteAnswer(NULL){}

WorldExt::WorldExt(const WorldExt& WE)
:World(WE),MyChild(NULL),MyCompleteAnswer(NULL) {}

WorldExt::WorldExt()
:World(Problem(),Finisher(C13,D13,H13,S13) ),MyChild(NULL),MyCompleteAnswer(NULL){}


WorldExt* WorldExt::copy() const
{
	return new WorldExt(P,F,History);
}

bool WorldExt::ChildRoutine(bool flag, WorldExt* that, int Level)
{
	//cout<< this->str()<<endl;    //code for debugging
	if (flag)
	{
		//cout<< that->str()<<endl;  // code for debugging
		if (!that->isDead())
		{
			//要有快速解可以在這裡加that.AutoSafeUp();但是這不是正規的做法..
			WorldExt* Copy=that->copy();
			Copy->ALLUP();
			if (Copy->isComplete())
			{
				that->ALLUP();				
			}
			delete Copy;
			if (that->isComplete())
			{
				MyCompleteAnswer->push_back(*that);
				return true;
			}else
			{
				MyChild->push_back(*that);
				return false;
			}
		}
	}
	return false;
}
void WorldExt::makeChild(int Level,vector<WorldExt>* ptrChild, vector<WorldExt>* ptrCompleteAnswer)
{
	if (ptrChild==NULL)
		MyChild=new vector<WorldExt>();
	else
		MyChild=ptrChild;

	if (ptrCompleteAnswer==NULL)
		MyCompleteAnswer=new vector<WorldExt>();
	else
		MyCompleteAnswer=ptrCompleteAnswer;

	//cout<<endl<< this->P.str()<<endl;

	if (!makeChild0(Level))    //MOVELINE
	{
		if (!makeChild1(Level))  //CONNECT
		{
			if (!makeChild2(Level))//CONNECT(Cell,8)+DOWN(Cell)
			{
				if (!makeChild3AB(Level)) //FINISH
				{
					if (!makeChild4(Level))//DOWN(L1a)+DOWN(L1b)
					{
						makeChild5(Level); //POP(L1a)
					}					
				}
			}
		}
	}
	
	//std::sort(MyChild->begin(), MyChild->end(), CardNum_TotalAV);  //為求快速,所以暫時REM此行

}
bool WorldExt::makeChild0(int Level)  //MOVELINE
{
	if (P.FirstBlankLine()>=1)
	{
		for (int j=1; j<=8; j++)
		{
			Card hand=P.Peek(j);
			if (hand!=NULL)
			{
				WorldExt* that=this->copy();
				if (!ChildRoutine(that->MOVELINE(NULL,hand),that,Level))
				{	delete that; continue;
				}else
				{	delete that; return true;
				}
			}
		}
	}
	int i,j;
	for ( i=1; i<=8; i++)
	{
		for ( j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Card upper=this->P.Peek(i);
				Card lower=this->P.Peek(j);
				if (lower!=NULL  &&	upper!=NULL	&&		//在這裡不檔(upper==NULL)
					lower.GetSuit()!=NONE &&
					upper.GetSuit()!=NONE)
				{
					WorldExt* that=(this->copy());
					if (!ChildRoutine(that->MOVELINE(upper,lower),that,Level))
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
bool WorldExt::makeChild1(int Level)  //CONNECT(8,8)
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
						if (!ChildRoutine(that->CONNECT(upper,lower),that,Level))
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
bool WorldExt::makeChild2(int Level)  //CONNECT(Cell,8)+DOWN(Cell)
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
					if (!ChildRoutine(that->CONNECT(upper,lower),that,Level))
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
				if (!ChildRoutine(that->DOWN(lower),that,Level))
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
bool WorldExt::makeChild3AB(int Level)  //FINISH
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
			if (!ChildRoutine(that->FINISH(B[i]),that,Level))
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
bool WorldExt::makeChild4(int Level)  //DOWN(L1a)+DOWN(L1b)
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
			if (!ChildRoutine(that->DOWN(B[i]), that,Level))
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
bool WorldExt::makeChild5(int Level)  //POP(L1a)
{
	if (P.Available()>0)
	{
		for (int i=1; i<=8; i++)
		{
			Card Hand=P.Peek(i);
			if (Hand!=NULL)
			{
				WorldExt* that=this->copy();
				int oldChildNumber=MyChild->size();
				if (!ChildRoutine(that->POP(Hand),that,Level))
				{
					int newChildNumber=MyChild->size();
					assert(newChildNumber-oldChildNumber<=1);
					delete that;   // 如果使用指標的設計要把這裡打掉
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
		if (Last.Action==ACTION_TYPE::CONNECT && Last.Card2==that)
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

void Dump(const vector<WorldExt>& vec,string filename)
{
	ofstream outfile(filename.c_str());
	outfile<<"int L[]={";
	for (int i=0; i<vec.size(); i++)
	{
		NP that(vec[i].P);
		vector<Card> hand=that.getVector();
		//that.PrintVector(hand);	
		outfile<<hand.size()<<",";
	}
	outfile<<"};\r\n";
	outfile<<"char stm[][70]={"<<endl;
	for (int i=0; i<vec.size(); i++)
	{
		NP that(vec[i].P);
		vector<Card> hand=that.getVector();
		//that.PrintVector(hand);	
		outfile<<"{";
		for (int j=0; j<hand.size(); j++)
		{
			outfile<< hand[j].estr()<<",";
		}
		outfile<<"},\r\n";
	}
	outfile<<"};"<<endl;
	for (int i=0; i<vec.size(); i++)
	{
		outfile<<endl<< vec[i].str()<<endl;
	}
}