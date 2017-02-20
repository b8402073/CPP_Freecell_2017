#include "World.h"
World::World()
:tmpNPItem(NULL),F(C13,D13,H13,S13)
{
}

World::World(int i)
:tmpNPItem(NULL),P(i),F(_Empty,_Empty,_Empty,_Empty)
{
}

World::World(const Problem& PP)
:tmpNPItem(NULL),P(PP),F(PP.Synthesize_Finisher())
{}

World::World(const Problem& PP,const Finisher&FF)
:tmpNPItem(NULL),P(PP),F(FF)
{
	Finisher tmp=P.Synthesize_Finisher();
	assert(tmp.equals(&F));
}

World::World(const Problem& PP,vector<HistoryItem> HH)
:tmpNPItem(NULL),P(PP),F(PP.Synthesize_Finisher())
{
	//std::copy(HH.begin(), HH.end(), History.begin());
	History.insert(History.end(), HH.begin(), HH.end());
}

World::World(const Problem& PP,const Finisher& FF,vector<HistoryItem> HH)
:tmpNPItem(NULL),P(PP),F(PP.Synthesize_Finisher())
{
	//std::copy(HH.begin(), HH.end(), History.begin());
	History.insert(History.end(), HH.begin(), HH.end());
}
World::World(const World& WW)
:tmpNPItem(NULL),P(WW.P), F(WW.F)
{
	//std::copy(WW.History.begin(), WW.History.end(), History.begin() );  //由BBS理解到這個寫法的問題
	History.insert(History.end(), WW.History.begin(), WW.History.end() );

	/*底下可以跑 */
	/*
	for (int i=0; i<WW.History.size(); i++)
	{
		History.push_back( WW.History[i] );
	}
	*/

}


World* World::copy() const
{
	return new World(P,F,History);
}
Card World::PeekCard(int line,int srow) const
{
	return P.PeekCard(line,srow);
}
Card World::FinisherTop(CardSuit S) const
{
	return F.Top(S);
}
bool World::CheckFinish() const
{
	for (int i=1; i<=8; i++)
	{
		if (F.Needed(P.Peek(i)))
			return true;
	}
	for (int i=0; i<P.GetBufferSize(); i++)
	{
		if (F.Needed(P.PeekBuffer(i)))
			return true;
	}
	return false;
}
void World::ReserveWorld()
{
	BeforeChange= new Problem(P);
	assert(bfChangeHistory.size()==0);
	//std::copy(History.begin(), History.end(), bfChangeHistory.begin());  //不知道為什麼這樣不可以跑
	bfChangeHistory.insert(bfChangeHistory.end(), History.begin(), History.end() );

	/*
	for (int i=0; i<History.size(); i++)
	{
		bfChangeHistory.push_back(History[i]);
	}
	*/
}
void World::ResumeWorld()
{
	ResumeWorld(BeforeChange,bfChangeHistory);
	ReleaseWorld();
}
void World::ResumeWorld(Problem* PP,vector<HistoryItem> HH)
{
	P= (*PP);
	F= P.Synthesize_Finisher();
	History.clear();
	//old : std::copy(bfChangeHistory.begin(), bfChangeHistory.end(), History.begin() );
	std::copy(bfChangeHistory.begin(), bfChangeHistory.end(), back_inserter(History) );
	ReleaseWorld();
}
void World::ReleaseWorld()
{
	bfChangeHistory.clear();
	delete BeforeChange;
}
bool World::MOVELINE(int srcLine,int dstLine)
{
	ReserveWorld();
	vector<Card> hand;
	if (P.Peek(dstLine)!= _Empty)
		hand=  GetDragonDestNotNull(P,srcLine, P.Peek(dstLine));
	else {
		hand=  GetDragonDestIsNull(P,srcLine);
		//如果把整列都抓了送到空行,實質上問題不會演進,所以要傳回false
		if (P.GetNowMaxPos(srcLine)+1==hand.size())
		{
			ReleaseWorld();
			return false;
		}
	}
	if (hand.size()<=1)  //牌太少就不做了
	{
		ReleaseWorld();
		return false;
	}
	for (int i=0; i<hand.size(); i++)
	{
		if( P.Fetch(srcLine)==_Empty)
		{
			ResumeWorld();
			return false;
		}
	}
	for (int i=hand.size()-1; i>=0; i--)
	{
		if (!P.Put(hand[i],dstLine))
		{
			ResumeWorld();
			return false;
		}
	}
	ReleaseWorld();
	ReleaseNPItem();
	return true;
}
bool World::MOVELINE(Card High,Card Low)  
//這裡不跑ReleaseNPItem()是因為底層做過了
{
	int src=(-1),dst=(-1);
	if (High!=_Empty)
	{
		dst=P.QuickWhereIs(High);
	}else 
	{
		dst= P.FirstBlankLine();
	}
	src= P.QuickWhereIs(Low);	
	if (src>=1 && dst>=1 && MOVELINE(src,dst))
	{
		History.push_back( ItemMoveLine(High,Low) );
		return true;
	}
	
	return false;
}
bool World::equals(const World* that) const
{
	return (P.equals(&(that->P)));
}
bool World::ValueEquals(const World *that) const
{
	return( P.ValueEquals(&(that->P)));
}
bool World::CONNECT(Card Upper,Card Lower)  //Update for ReleaseNPItem()
{
	Card hand=_Empty;
	if (Problem::Rule(Upper,Lower))
	{
		int dstLine=P.QuickWhereIs(Upper);
		int srcLine=P.QuickWhereIs(Lower);
		if (dstLine>=1)
		{
			if (srcLine==0)
			{
				hand=P.FetchBuffer(Lower);
			}else if (srcLine>=1)
			{
				hand=P.Fetch(srcLine);
			}else
			{
				return false;
			}
			if (P.Put(hand,dstLine))
			{
				History.push_back( ItemConnect(Upper,Lower));
				ReleaseNPItem();
				return true;
			}else
			{
				if (srcLine==0)
					P.PutBuffer(hand);
				else
					P.Put(hand,srcLine);
				return false;
			}
		}
	}
	return false;
}
bool World::FINISH(Card that)   //update for ReleaseNPItem();
{
	Card hand=_Empty;
	if (F.Needed(that))
	{
		hand=P.FetchBuffer(that);
		if (hand)
		{
			History.push_back(ItemFinish(hand));
			ReleaseNPItem();
			return F.add(hand);
		}else
		{
			hand=P.Fetch(P.QuickWhereIs(that));
			if (hand)
				History.push_back(ItemFinish(hand));
			ReleaseNPItem();
			return F.add(hand);
		}
		P.PutBuffer(hand);
		return false;
	}
	return false;
}
bool World::POP(Card that)  //Update for ReleaseNPItem();
{
	if (P.GetBufferSize() < 4)
	{
		int srcLine=P.QuickWhereIs(that);
		if (srcLine>=1)
		{
			History.push_back(ItemPop(that));
			ReleaseNPItem();
			return P.PutBuffer(P.Fetch(srcLine));
		}
	}
	return false;
}
bool World::_DOWN(Card that,int dstLine)  //Update for ReleaseNPItem();
{
	ReserveWorld();
	Card hand=_Empty;
	if (dstLine>=1 && dstLine<=8 && P.Peek(dstLine)==_Empty)
	{
		int srcLine=P.QuickWhereIs(that);
		if (srcLine>=1)
			hand=P.Fetch(srcLine);
		else if (srcLine==0)
			hand=P.FetchBuffer(that);
		else
		{
			ReleaseWorld();
			return false;
		}
		History.push_back(ItemDown(that));
		ReleaseWorld();
		ReleaseNPItem();
		return P.Put(hand,dstLine);
	}
	ReleaseWorld();
	return false;
}
bool World::DOWN(Card that)
//這裡不做ReleaseNPItem()是因為底層做過了
{
	if (P.QuickWhereIs(that)>=0 && P.FirstBlankLine()>=1)
	{
		return _DOWN(that,P.FirstBlankLine());
	}
	return false;
}
bool World::AutoSafeUp()
{
	if (this->isComplete())
		return true;
	bool flag;
	bool ret=false;
	do
	{
		flag=false;
		vector<Card> Buf= P.BufferToVector();
		for (int i=0; i<Buf.size(); i++)
		{
			if (F.Needed(Buf[i]))
			{
				if (F.SafeCardUp(Buf[i]))
				{
					if (FINISH(Buf[i]))
					{
						flag=ret=true;
					}
				}
			}
		}
		for (int i=1; i<=8; i++)
		{
			Card hand=P.Peek(i);
			if (hand!=_Empty && hand.GetSuit()!=NONE)
			{
				if (F.Needed(hand))
				{
					if (F.SafeCardUp(hand))
					{
						if (FINISH(hand))
						{
							flag=ret=true;
						}
					}
				}
			}
		}
	}while(flag);
	return ret;
}
bool World::ALLUP()
{
	bool ret=false;
	while( World::UserFinish(this).size()>0)
	{
		if (this->AutoSafeUp())
			ret=true;
		vector<Card> hand=World::UserFinish(this);
		for (int i=0; i<hand.size(); i++)
		{
			if (FINISH(hand[i]))
				ret=true;
		}
	}
	return ret;
}
bool World::isComplete() const
{
	return (P.CardNum()==0);
}
string World::HistoryToString(int StartPos,bool head) const
{
	static char _buf[5];
	int sz=History.size();
	string ret=( (head) ? "HistorySize("+ string( itoa(sz,_buf,10) )  +"):[" : "");	
	if (StartPos>=0 && StartPos<=sz)
	{
		for (int i=StartPos; i<sz; i++)
		{
			ret+= ItemToString(History[i]);
			ret+= ";";
		}
		if (head)
			ret+= "]\r\n";
		return ret;
	}
	return "HistoryToString: [Out Of Range]\r\n";
}
string World::str() const
{
	return str(true,true);
}
string World::str(bool ShowHistory, bool ShowFinisher) const
{
	string ret;
	if (ShowHistory)
		ret+=HistoryToString(0,true);
	if (ShowFinisher)
		ret+= ("Finisher:"+F.str()+"\r\n");
	ret+= (P.str() );
	return ret;
}
bool World::isDead() const
{
	if (P.Available()>0)
		return false;
	for (int i=0; i< P.GetBufferSize(); i++)
	{
		Card BufCard= P.PeekBuffer(i);
		if (F.Needed(BufCard))
			return false;
		for (int j=1; j<=8; j++)
		{
			Card there= P.Peek(j);
			if (Problem::Rule(there,BufCard))
				return false;
		}
	}
	for (int i=1; i<=8; i++)
	{
		//因為已經知道不會有空行
		if (F.Needed(P.Peek(i)))
			return false;
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				if (Problem::Rule(P.Peek(i), P.Peek(j)))
					return false;
			}
		}
	}
	return true;
}
vector<Card>  World::UserFinish(const World *inn)
{
	vector<Card> ret;
	World* inW= inn->copy();
	bool flag;
	do
	{
		flag=false;
		for (int i=0; i<inW->P.GetBufferSize() ; i++)
		{
			Card hand=inW->P.PeekBuffer(i);
			if (inW->F.Needed(hand))
			{
				if (inW->FINISH(hand))
				{
					ret.push_back(hand);
					flag=true;
					break;
				}
			}
		}
		for (int i=1; i<=8; i++)
		{
			Card hand=inW->P.Peek(i);
			if (hand!=_Empty && hand.GetSuit()!=NONE)
			{
				if (inW->F.Needed(hand))
				{
					if (inW->FINISH(hand))
					{
						ret.push_back(hand);
						flag=true;
					}
				}
			}
		}
	}while(flag);
	return ret;
}
string World::GetBufStrings() const
{
	string ret;
	int sz= P.GetBufferSize();
	for (int i=0; i<sz-1; i++)
	{
		ret += (P.PeekBuffer(i).str()+",");
	}
	if (sz>=1)
		ret+= (P.PeekBuffer(sz-1).str());
	return ret;
}
string World::GetStrings(int LineNum) 
//暫時用跑起來很慢的做法,這個函式不一定會用到
{
	string ret;
/*	
	// old code
	NP that(P);
	int i;
	int sz= that.OutputArr.GetNowMaxPos(LineNum)+1;
	for (i=0; i< sz-1; i++)
	{
		ret+= (that.OutputArr.PeekCard(LineNum,i).str()+",");
	}
	if (sz>=1)
		ret += (that.OutputArr.PeekCard(LineNum,i).str());
	return ret;
*/
	if (!tmpNPItem)
	{
		tmpNPItem=new NP(P);
	}
	int sz= tmpNPItem->OutputArr.GetNowMaxPos(LineNum)+1;
	int i;
	for (i=0; i<sz-1; i++)
	{
		ret+= (tmpNPItem->OutputArr.PeekCard(LineNum,i).str()+",");
	}
	if (sz>=1)
		ret+= (tmpNPItem->OutputArr.PeekCard(LineNum,i).str());
	return ret;
}
//////////////////////////////////////////////////以下是Gamer的部分
string World::Finisher_View(Card that,const Finisher& FF)
{
	static string SuitChar[]={"c","d","h","s","@"};
	static char _buf[4];
	int N= Finisher_Num(that,FF);
	if (N!=(-14))
	{
		if (N>=10)
			return(SuitChar[that.GetSuit()]+itoa(N,_buf,10));
		else
			return(" "+SuitChar[that.GetSuit()]+itoa(N,_buf,10));
	}
	return "GGY";
}
int World::Finisher_Num(Card that,const Finisher& FF)
{
	if (that)
	{
		Card thattop= FF.Need(that.GetSuit());
		if (thattop)
			return (that.GetValue() - thattop.GetValue());
	}
	return -14;
}
int World::Total_Obstruction_AV(const World& that,bool debug)
{
	int ret=0;
	for (int i=1; i<=8; i++)
	{
		if (debug)
			cout<<"Line"<<i<<":"<<endl;
		for (int j=0; j<21; j++)
		{
			Card hicard=that.P.PeekCard(i,j);			
			if (hicard==_Empty || j==20)
				break;
			for (int k=j+1; k<21; k++)
			{
				Card lowcard=that.P.PeekCard(i,k);
				if (lowcard== _Empty)
					break;
				else
				{
					int high_num= Finisher_Num(hicard,that.F);
					int low_num=Finisher_Num(lowcard,that.F);
					int av= that.P.Available();
					if (lowcard.GetSuit()==hicard.GetSuit())
					{
						if (high_num < low_num)
						{
							ret+=1;
							if (debug)
							{
								cout<<"<"
									<<Finisher_View(hicard,that.F)
									<<"="
									<<Finisher_View(lowcard,that.F)
									<<">";
							}
						}
					}else
					{
						if (low_num - high_num > av)
						{
							ret+=1;
							if (debug)
							{
								cout<<"<"
									<<Finisher_View(hicard,that.F)
									<<"="
									<<Finisher_View(hicard,that.F)
									<<">";
							}
						}
					}
				}
			}
		}
		if (debug)
			cout<<endl;
	}
	return ret;
}
int  World::Total_Obstruction_AV(const World& that)
{
	return World::Total_Obstruction_AV(that,false);
}
bool World::CardNum_TotalAV(const World& X,const World& Y)
{
	const bool WHEN_WE_DONT_CARE=false;
	int x1=X.P.CardNum();
	int y1=Y.P.CardNum();
	if (x1<y1)
		return true;
	else if (x1>y1)
		return false;
	else
	{
		int x2= World::Total_Obstruction_AV(X);
		int y2= World::Total_Obstruction_AV(Y);
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

World::~World()
{
	ReleaseNPItem();
}