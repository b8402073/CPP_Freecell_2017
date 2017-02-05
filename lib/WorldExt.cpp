#include <ctime>
#include "WorldExt.h"
U::U(){}
bool U::SubExist(const vector<WorldExt>& V, const WorldExt& that) const
{
	if (V.size()>0)
	{
		for (int i=0; i<V.size(); i++)
		{
			if (V[i].ValueEquals(&that))
				return true;
		}
	}
	return false;
}
int U::WorldNum() const
{
	int ret=0;
	for (int i=0; i<22; i++)
	{
		for (int j=0; j<22; j++)
		{
			for (int k=0; k<5; k++)
			{
				ret+= (Data[i][j][k].size());
			}
		}
	}
	return ret;
}
int U::WorldMax() const
{
	int ret=0;
	for (int i=0; i<22; i++)
	{
		for (int j=0; j<22; j++)
		{
			for (int k=0; k<5;k++)
			{
				int that=Data[i][j][k].size();
				if (that>ret)
					ret=that;
			}
		}
	}
	return ret;
}
void U::Clear()
{
	for (int i=0; i<22; i++)
	{
		for (int j=0; j<22; j++)
		{
			for (int k=0; k<5; k++)
			{
				Data[i][j][k].clear();
			}
		}
	}
}
bool U::Add(WorldExt that)
{
	int i= that.P.MaxOf_NowMaxPos();
	int j= that.P.SecondOf_NowMaxPos();
	int k= that.P.GetBufferSize();
	Data[i][j][k].push_back(that);
	return true;
}
bool U::Exist(WorldExt that) const
{
	int i=that.P.MaxOf_NowMaxPos();
	int j=that.P.SecondOf_NowMaxPos();
	int k=that.P.GetBufferSize();

	return SubExist(Data[i][j][k],that);
}
bool U::Remove(WorldExt that)
{
	int A=that.P.MaxOf_NowMaxPos();
	int B=that.P.SecondOf_NowMaxPos();
	int C=that.P.GetBufferSize();
	for (int i=0; i< Data[A][B][C].size(); i++)
	{
		if (Data[A][B][C][i].ValueEquals(&that))
		{
			Data[A][B][C].erase( Data[A][B][C].begin()+i, Data[A][B][C].begin()+(i+1));
			return true;
		}
	}
	return false;
}
WorldExt*  U::EE(WorldExt that)
{
	int A=that.P.MaxOf_NowMaxPos();
	int B=that.P.SecondOf_NowMaxPos();
	int C=that.P.GetBufferSize();
	for (int i=0; i< Data[A][B][C].size(); i++)
	{
		if (that.ValueEquals(&(Data[A][B][C][i])))
		{
			return &(Data[A][B][C][i]);
		}
	}
	return NULL;
}
int U::Locate(WorldExt that) const
{
	int A=that.P.MaxOf_NowMaxPos();
	int B=that.P.SecondOf_NowMaxPos();
	int C=that.P.GetBufferSize();
	for (int i=0; i<Data[A][B][C].size(); i++)
	{
		if (that.ValueEquals(&(Data[A][B][C][i])))
			return i;
	}
	return -1;
}
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
			//�n���ֳt�ѥi�H�b�o�̥[that.AutoSafeUp();
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
				//�p�GUOne�w�g�s�bthat
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
	if (!makeChild0(Level,HiLevel))
	{
		if (!makeChild1(Level,HiLevel))
		{
			if (!makeChild2(Level,HiLevel))
			{
				if (!makeChild3AB(Level,HiLevel))
				{
					if (!makeChild4(Level,HiLevel))
					{
						makeChild5(Level,HiLevel);
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
	//std::sort(Child.begin(), Child.end(), CardNum_TotalAV);  //���D�ֳt,�ҥH�Ȯ�REM����
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
	//�Ѧ�History����Ʈ����i��o�ͪ�Ping-Pong�{�H
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
			//��o�̴N�T�w��Ping-Pong�X�{�F,�n����
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
	for (int i=1; i<4; i++)    //�i��|�h��MakeChild
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
					//�o�@�s�Ѥ��Χ�F
					return NoAnswer;
				}
			}

			if (inn[0].isComplete())
			{
				isComplete=true;
				return inn[0];
			}else if (isComplete)
			{
				return NoAnswer;
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
				return NoAnswer;
		}else
			return NoAnswer;
	}
	return NoAnswer;
}
/***
 * �H�K��@�Ӹ�
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
 *  ��@�ӦX�z���θ�
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
	return NoAnswer;
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