#include "Finisher.h"
#include "problem.h"


byte Problem::GetNowMaxPos(byte Line) const 
{
	assert(Line>=1 && Line<=8);
	byte ret= NowMaxPos[Line-1];
	assert(ret>= (-1));      //可以傳回-1是因為有空列 
	return ret;
}
vector<Card> Problem::BufferToVector() const
{
	return MB.toVector();
}
int Problem::SearchBuffer(Card that) const
{
	return MB.Search(that);
}
byte Problem::GetBufferSize() const
{
	return MB.GetSize();
}

Card Problem::PeekBuffer(int pos) const
{
	assert(pos>=0 && pos<4);
	return MB.get(pos);
}
Card Problem::PeekCard(int col,int row) const
{
	assert(col>=1 && col<=8);
	//assert(row>=0 && row<= GetNowMaxPos(col) );  //加入NP之後就不跑這段了
	return cardarr[col-1][row];
}
void Problem::Upd_NowMaxPos() 
{
	for (byte i=0; i<8; i++)
	{
		byte j=0;
		while(cardarr[i][j]>0)
		{
			j++;
		}
		j--;
		NowMaxPos[i]=j;  
	}
}

Problem::Problem()
{
	Upd_NowMaxPos();
}
Problem::Problem(const Buffer& thatmb)
:MB(thatmb)
{
	Upd_NowMaxPos();
}
Problem::Problem(const Card arr[][21], const byte _thatNowMaxPos[],const Buffer& thatBuffer)
:MB(thatBuffer)
{
	copy_2d_arr(cardarr,arr);
	std::copy(_thatNowMaxPos,_thatNowMaxPos+8, NowMaxPos);	
	MB=thatBuffer;
	
}
Problem::Problem(const Problem& inn)
:MB(inn.MB)
{
	copy_2d_arr(cardarr,inn.cardarr);
	std::copy(inn.NowMaxPos,inn.NowMaxPos+8, NowMaxPos);
	
}
Problem* Problem::copy() const
{
	return new Problem(cardarr,NowMaxPos,MB );
}
Problem::Problem(unsigned int Number)
{	
	byte i; int j;
	byte wLeft=52;
	srand(Number);
	Card deck[52];
	for (i=1; i<=52; i++)
		deck[i-1]=i;
	for (i=0; i<52; i++)
	{
		j=rand()%wLeft;
		cardarr[i%8][i/8]=deck[j];
		wLeft--;
		deck[j]=deck[wLeft];
	}
	for (int t=0; t<4; t++) {
		NowMaxPos[t]=6;
		assert(cardarr[t][NowMaxPos[t]]!=_Empty);
	}
	for (int t=4; t<8; t++) {
		NowMaxPos[t]=5;
		assert(cardarr[t][NowMaxPos[t]]!=_Empty);
	}
	
}


Problem::Problem(const Card arr[][21],const Buffer& thatmb)
:MB(thatmb)
{
	copy_2d_arr(cardarr,arr);
	Upd_NowMaxPos();
}
Problem::~Problem()
{
	
}

bool Problem::Rule(Card upper, Card lower) 
{
	if (upper==_Empty && lower>_Empty)
		return true;
	if (upper.GetValue()- lower.GetValue() ==1 &&
		upper.isRed() != lower.isRed() )
		return true;
	return false;
}
Card Problem::Peek(int srcLine) const
{
	assert(srcLine>=1 && srcLine<=8);
	return cardarr[srcLine-1][NowMaxPos[srcLine-1]];
}
Card Problem::Fetch(int srcLine) 
{
	Card ret=_Empty;
	if (srcLine>=1 && srcLine<=8)
	{
		if (cardarr[srcLine-1][0] >0)
		{
			ret=cardarr[srcLine-1][NowMaxPos[srcLine-1]];
			cardarr[srcLine-1][NowMaxPos[srcLine-1]]=_Empty;
			--NowMaxPos[srcLine-1];
		}
	}
	return ret;
}
Card Problem::FetchBuffer(Card that)
{
	if (that!=_Empty)
	{
		if (MB.Search(that)>=0)
		{
			MB.Remove(that);
			return that;
		}
	}
	return _Empty;
}
bool Problem::Put(Card that, byte dstLine)
{
	assert(dstLine>=1 && dstLine<=8);
	if (NowMaxPos[dstLine-1]<=19)
	{
		if (that!=_Empty)
		{
			cardarr[dstLine-1][NowMaxPos[dstLine-1]+1]=that;
			++NowMaxPos[dstLine-1];
			return true;
		}
	}
	return false;
}
bool Problem::PutBuffer(Card that)
{
	if (MB.Available()>0 && MB.Search(that)<0)
		return MB.Add(that);
	return false;
}
bool Problem::Pop(int srcLine)
{
	Card that=Fetch(srcLine);
	if (that!=_Empty)
	{
		if (MB.Available()>=1)
			return MB.Add(that);
		else if (HowManyBlankLines()>=1)
		{
			return Put(that,FirstBlankLine() );
		}
	}
	bool ret=Put(that,srcLine);
	assert(ret);
	return false;
}
bool Problem::Down(Card that,int dstLine)
{
	assert(dstLine>=1 && dstLine<=8 && that!=_Empty);
	Card there=FetchBuffer(that);
	if (there!=_Empty)
	{
		if (Peek(dstLine)==_Empty)
			return Put(that,dstLine);
		else
			PutBuffer(there);
	}
	return false;
}
Card Problem::CARDFUNCTION(Card thatcard, int delta) const
{
	if (thatcard==_Empty || (MB.Search(thatcard)>=0) )
		return _Empty;
	int i,j=0;
	bool found=false;
	for (i=0; i<8; i++)
	{
		if (NowMaxPos[i]>=0)
		{
			for (j=0; j<=NowMaxPos[i]; j++)
			{
				if (cardarr[i][j]==thatcard) 
				{
					found=true;
					break;
				}
			}
			if (found)
				break;
		}
	}
	if (j+delta>=0 && j+delta<=20)
		return cardarr[i][j+delta];
	else
		return _Empty;
}
int Problem::WhereIs(Card thatcard) const
{
	if (thatcard!=_Empty)
	{
		for (int i=0; i<8; i++)
		{
			for (byte j=NowMaxPos[i]; j>=0; j--)
			{
				if (thatcard==cardarr[i][j])
					return(i+1);
			}
		}
		if (MB.Search(thatcard)>=0)
			return 0;
	}
	return -1;
}
Card Problem::AHead(Card that) const
{
	assert(that!=_Empty);
	int srcLine=WhereIs(that);
	if (srcLine>=1 && srcLine<=8)
	{
		int lastpos=NowMaxPos[srcLine-1];
		for (int i=0; i<=lastpos; i++)
		{
			if (that==cardarr[srcLine-1][i])
			{
				if (i!=0)
					return cardarr[srcLine-1][i-1];
				else
					return _Empty;
			}
		}
	}
	if (srcLine==0)
		throw runtime_error("This card is at MyBuffer");
	throw runtime_error("This card is not in the Problem");

}
int Problem::CardNum() const
{
	int sum=0;
	for (int i=0; i<8; i++)
	{
		sum += (NowMaxPos[i]+1);
	}
	sum += MB.GetSize();
	return sum;
}
byte Problem::POSITION(Card thatcard) const
{
	return POSITION(thatcard,WhereIs(thatcard) );
}
byte Problem::POSITION(Card thatcard,int srcLine) const
{
	if (srcLine>=1 && srcLine<=8)
	{
		if (thatcard!=_Empty)
		{
			for (int i=0; i<= NowMaxPos[srcLine-1]; i++)
			{
				if (thatcard==cardarr[srcLine-1][i])
					return i;
			}
		}
	}
	return -1;
}
vector<byte> Problem::BlankLine() const
{
	vector<byte> ret;
	for (int i=0; i<8; i++)
	{
		if (NowMaxPos[i]== (-1))
			ret.push_back( (byte) (i+1) );
	}
	return ret;
}
vector<byte> Problem::OneCardLine() const
{
	vector<byte> ret;
	for (int i=0; i<8; i++)
	{
		if (NowMaxPos[i]==0)
			ret.push_back( (byte) (i+1) );
	}
	return ret;
}
int Problem::FirstBlankLine() const
{
	for (int i=0; i<8; i++)
	{
		if (NowMaxPos[i]==(-1))
			return(i+1);
	}
	return (-1);
}
int Problem::HowManyBlankLines() const
{
	int ret=0;
	for (int i=0; i<8; i++)
	{
		if (NowMaxPos[i]== -1)
			++ret;
	}
	return ret;
}
int Problem::HowManyOneCardLines() const
{
	int ret=0;
	for (int i=0; i<8; i++)
	{
		if (NowMaxPos[i]==0)
			++ret;
	}
	return ret;
}
int Problem::OneCardSum() const
{
	int ret=0;
	for (int i=0; i<8; i++)
	{
		if (NowMaxPos[i]==0)
			ret+= cardarr[i][0].GetValue();
	}
	return ret;
}
byte Problem::MaxOf_NowMaxPos() const
{
	return( *std::max_element(NowMaxPos,NowMaxPos+8) );
}
byte Problem::SecondOf_NowMaxPos() const
{
	/*
	old code:  好寫易懂
	vector<byte> tmp;
	for (int i=0; i<8; i++)
	{
		tmp.push_back(NowMaxPos[i]);
	}
	std::sort(tmp.begin(), tmp.end() );
	return tmp[6];
	*/
	//NEW CODE is more elegant.
	byte tmp[8];
	std::copy(NowMaxPos,NowMaxPos+8,tmp);
	std::make_heap(tmp,tmp+8);
	return std::max(tmp[1], tmp[2] );
}
byte Problem::SortOf_NowMaxPos(int LineOrder) const 
//LineOrder==1 Get Minimum, LineOrder==8 Get Maximum
{
	if (LineOrder>=1 && LineOrder<=8)
	{
		/* old code
		vector<byte> tmp;
		for (int i=0; i<8; i++)
		{
			tmp.push_back(NowMaxPos[i]);
		}
		*/
		//NEW CODE is more elegant.
		byte tmp[8];
		std::copy(NowMaxPos,NowMaxPos+8,tmp);
		std::sort(tmp,tmp+8 );
		return tmp[LineOrder-1];
	}
	return -1;
}
string Problem::str() const
{
	int m=MaxOf_NowMaxPos();
	string ret;
	ret.append("Buffer: ");
	ret.append(MB.str() +"\r\n");
	for (int row=0; row<=m; row++)
	{
		string Line;
		for (int col=0; col<8; col++)
		{
			if (cardarr[col][row]>0)
				Line.append("["+cardarr[col][row]._str()+"]");
			else
				Line.append("[@@@]");
		}
		Line.append("\r\n");
		ret.append(Line);
	}
	return ret;
}
string Problem::str9() const
{
	string ret;
	ret.append("\"");
	for (int i=0; i< MB.GetSize()-1; i++)
		ret.append(MB.get(i).str()+",");
	ret.append(MB.get(MB.GetSize()-1).str() );
	ret.append("\"\n");
	for (int Line=1; Line<=8; Line++)
	{
		ret.append("\"");
		for (int i=0; i<=GetNowMaxPos(Line)-1; i++)
		{
			ret.append( cardarr[Line-1][i].str() +",");
		}
		ret.append(cardarr[Line-1][GetNowMaxPos(Line)].str()+"#");
		ret.append("\"\n");
	}
	return ret;
}
bool Problem::equals(const Problem *that) const
{
	if (that!=NULL)
	{
		//其實數學邏輯上只比後面的二維陣列就充分了,先比Buffer可以算是shortcut
		return MB.equals(&(that->MB)) && CompareCardArr(this->cardarr, that->cardarr);
	}
	return false;
}
byte Problem::QuickWhereIs(Card that) const
{
	if (MB.Search(that)>=0)
		return 0;
	for (int i=1; i<=8; i++)
	{
		Card hand=Peek(i);
		if (hand!=_Empty)
		{
			if (hand==that)
				return i;
		}
	}
	return -1;
}
byte Problem::Synthesize(CardSuit S) const
{
	byte ret=0;
	for (int i=1; i<=13; i++)
	{
		Card that=GetCard(i,S);
		int L= WhereIs(that);
		if (L<0)
			ret=i;
		else
			break;
	}
	return GetCard(ret,S);
}
Finisher Problem::Synthesize_Finisher() const
{
	Card arr[4];
	arr[0]=Synthesize(CLUB);
	arr[1]=Synthesize(DIAMOND);
	arr[2]=Synthesize(HEART);
	arr[3]=Synthesize(SPADE);
	return  Finisher(arr);  
}
bool Problem::IsValid() const
{
	Finisher FF=Synthesize_Finisher();
	for (int iit=0; iit<4; iit++)
	{
		CardSuit it=(CardSuit) iit;
		Card c=FF.Top(it);
		if (c!= _Empty)
		{
			for (int v=c.GetValue()+1; v<=13; v++)
			{
				Card cc= GetCard(v,it);
				if (WhereIs(cc)<0) 
				{
					throw runtime_error("Corruptive Card("+cc.str()+")");
					return false;
				}
			}
		}else
		{
			for (int v=1; v<=13; v++)
			{
				Card cc=GetCard(v,it);
				if (WhereIs(cc)<0 && !FF.Search(cc))
				{
					throw runtime_error("Corruptive card("+cc.str()+")");
					return false;
				}
			}
		}
	}
	if (MB.GetSize()>4)
		return false;
	
	vector<Card> CheckDuplicate;
	for (int i=0; i< MB.GetSize(); i++)
	{
		CheckDuplicate.push_back(MB.get(i));
	}
	for (int i=1; i<=8; i++)
	{
		for (int j=0;j<= NowMaxPos[i-1]; j++)
		{
			if (cardarr[i-1][j]==0) 
			{
				string message="Empty in cardarr at col=";//+_itoa(i)+" row="+_itoa(j);
				message += i;
				message += " row=";
				message += j;
				throw  runtime_error(message);
				return false;
			}
			else
				CheckDuplicate.push_back(cardarr[i-1][j]);
		}
	}
	std::sort(CheckDuplicate.begin(),CheckDuplicate.end());
	for (int i=0; i<CheckDuplicate.size()-1; i++)
	{
		if (CheckDuplicate[i]==CheckDuplicate[i+1])
		{
			throw runtime_error("Duplicate Card:"+CheckDuplicate[i].str() );
			return false;
		}
	}
	return true;
}

bool Problem::ValueEquals(const Problem* that) const
{
	const byte* ret1= this->getBytes();
	const byte* ret2= that->getBytes();
	int i;
	for (i=0; ret1[i]!=_EndOfStream  && ret2[i]!=_EndOfStream ; i++)
	{
		if (ret1[i]!= ret2[i])
		{
			delete[] ret1;  delete[] ret2;  return false;
		}
	}
	bool ret= (ret1[i]==ret2[i]);
	delete[] ret1; delete[] ret2;
	return ret;
}

byte* Problem::getBytes() const
{
	NP that(*this);
	return NP::VectorToBytes(that.getVector());
}

NP::NP(const Problem& inn)
:Input(inn)
{
	for (int i=0; i<inn.GetBufferSize(); i++)
	{
		OutputArr.PutBuffer(inn.PeekBuffer(i));
	}
	Normalize();
	for (int i=1; i<=8; i++)
	{
		byte L= NormLineOrder[i-1];
		Card that;
		do 
		{
			that=Input.Fetch(L);
			if (that!=_Empty) 
				assert(OutputArr.Put(that,i)==true);
			else
				break;

		}while(true);
	}
}
void NP::Normalize()
{
	struct Tuple 
	{
	public:
		int LineNumber;
		int LineLength;
		Card Top;
	};
	struct CompTuple
	{
		bool operator()(Tuple prev,Tuple next)
		{
			if (prev.LineLength < next.LineLength)
				return false;
			else if (prev.LineLength> next.LineLength)
				return true;
			else 
			{
				if (prev.Top < next.Top)
					return false;
				else if (prev.Top > next.Top)
					return true;				
			}
			return false;
		}
	}myinstance;
	vector<Tuple> Hand;
	for (int i=1; i<=8; i++)
	{
		Tuple T;
		T.LineNumber=i; 
		T.LineLength=(Input.GetNowMaxPos(i)+1);
		//T.Top=cardarr[i-1][0];
		T.Top=Input.PeekCard(i,0);
		Hand.push_back(T);		
	}
	std::sort(Hand.begin(),Hand.end(),myinstance);
	for (int i=0; i<Hand.size(); i++)
	{
		NormLineOrder[i]= Hand[i].LineNumber;
	}
}
vector<Card> NP::getVector()
{
	vector<Card> ret= OutputArr.GetBuffer().toVector();		
	ret.push_back( _Empty);
	int j=0;
	while(j<21)
	{	
		if (OutputArr.PeekCard(1,j)==_Empty)
			break;
		for (int i=1; i<=8; i++)
		{
			Card that= OutputArr.PeekCard(i,j);
			if (that==_Empty) 
			{
				ret.push_back(that);
				break;
			}else
				ret.push_back(that);
		}
		j+=1;
	}
	if (ret[ ret.size()-1 ] ==_Empty )
		ret[ ret.size()-1 ] = _EndOfStream;
	else
		ret.push_back( _EndOfStream);
	return ret;
}
byte* NP::VectorToBytes(vector<Card> that)
{	
	byte* ret=new byte[that.size()];
	//std::copy( that.begin(), that.end(), ret);   //@@? why this is not safe?
	for (int i=0; i<that.size(); i++)
	{
		ret[i]= that[i];
	}
	return ret;
}
void NP::PrintVector(vector<Card> that)
{
#define STREAM   //why this directive can't be put in Line1?
#ifdef STREAM
	cout<<"Card stream[]={";
#else
	cout<<"[";
#endif
	for (int i=0; i<that.size()-1; i++)
	{
		cout<< that[i].estr()<<",";
	}
	cout<< that[ that.size()-1 ].estr();
#if defined(STREAM)
	cout<<"};"<<endl;
#else
	cout<<"]"<<endl;
#endif

}
Problem NP::BytesToProblem(const byte* ptr)
{
	Problem ret;
	int i;
	for (i=0; ptr[i]!= _Empty ; i++)   
	{
		if (ptr[i]== _EndOfStream)
			return ret;
		ret.PutBuffer(ptr[i]);
	}
	vector< vector<Card>* > Hand; int HandCount=0;
	i++;
	while( ptr[i]!= _EndOfStream)
	{
		Hand.push_back( new vector<Card> ); HandCount+=1;
		while(ptr[i]!= _Empty && ptr[i]!= _EndOfStream)
		{
			Hand[HandCount-1]->push_back(ptr[i]);
			i++;
			if (Hand[HandCount-1]->size()==8) 
			{
				i--;
				break;
			}
		}
		if (ptr[i]!= _EndOfStream)
			i++;
	}
	
	for (int i=HandCount-1; i>=0; i--)
	{
		for (int j=1; j<= Hand[i]->size(); j++)
		{
			vector<Card>* that=Hand[i];
			ret.Put(that->at(j-1),j);
		}
		delete Hand[i];
	}
	return ret;
}

vector<Card> _GetDragon(const Problem& P, int srcLine)
{
	vector<Card> ret;
	Card first=P.Peek(srcLine);
	if (first!=_Empty && first.GetSuit()!=NONE)
	{
		ret.push_back(first);
		Card second=P.AHead(first);
		while(second!=_Empty && Problem::Rule(second,first)) 
		{
			ret.push_back(second);
			first=second;
			second=P.AHead(second);
		}
	}
	return ret;
}
vector<Card> GetDragonDestNotNull(const Problem& P,int srcLine,Card cut)
{
	vector<Card> ret= _GetDragon(P,srcLine);
	int delta= ret.size()- P.Available() -1;
	//step1 依照P.Available()來減少抓牌的數目
	if (delta>0)
	{
		ret.erase(ret.end()-delta, ret.end() );
	}	
	//step2 依照CUT來減少抓牌的數目
	if (cut!=NULL)
	{
		int sz=ret.size();
		int delStartPos=(-999);
		vector<Card> delete_me;
		for (int i=0; i<sz; i++)
		{
			Card hand=ret[i];
			if (Problem::Rule(cut,hand))
			{
				delStartPos=i;
				break;
			}
		}
		if (delStartPos>=0)
			ret.erase(ret.begin()+delStartPos+1, ret.end() );
	}
	//step3要回傳前要確定CUT牌與要回傳的牌要能接起來,否則把ret清空不傳了
	if (Problem::Rule(cut,ret[ret.size()-1]))
		return ret;
	else
	{
		ret.clear();
		return ret;
	}
}
vector<Card> GetDragonDestIsNull(const Problem& P,int srcLine)
{
	vector<Card> ret=_GetDragon(P,srcLine);
	const int Max=P.Available();
	if (ret.size() > Max)
	{
		const int ExcessElementNum= ret.size()-Max;
		ret.erase(ret.end() - ExcessElementNum, ret.end() );
	}
	return ret;
}


string NP::str()
{
	return OutputArr.str();
}