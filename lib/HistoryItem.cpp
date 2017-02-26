#include "HistoryItem.h"
HistoryItem ItemFinish(Card that)
{
	assert(that>=C1 && that<=S13);
	HistoryItem ret;
	ret.Action=FINISH;
	ret.Card1=that;
	return ret;
}
HistoryItem ItemPop(Card that)
{
	assert(that>=C1 && that<=S13);
	HistoryItem ret;
	ret.Action=POP;
	ret.Card1=that;
	return ret;
}
HistoryItem ItemDown(Card that)
{
	assert(that>=C1 && that<=S13);
	HistoryItem ret;
	ret.Action=DOWN;
	ret.Card1=that;
	return ret;
}
HistoryItem ItemConnect(Card upper,Card lower)
{
	assert(upper>=C2 && upper<=S13 && lower<upper && lower>=C1);
	assert(lower.isRed()!=upper.isRed());
	assert(upper.GetValue()-lower.GetValue()==1);
	HistoryItem ret;
	ret.Action=CONNECT;
	ret.Card1=upper;
	ret.Card2=lower;
	return ret;
}
HistoryItem ItemMoveLine(Card upper, Card lower)
{
	if (upper!= _Empty) 
	{
		assert(upper>=C2 && upper<=S13 && lower<upper && lower>=C1);
	}else 
	{
		assert(lower>=C1 && lower<=S13);
	}
	HistoryItem ret;
	ret.Action=MOVELINE;
	ret.Card1=upper;
	ret.Card2=lower;
	return ret;
}
string ItemToString(HistoryItem that)
{
	string append,head;
	switch(that.Action)
	{
	case MOVELINE:
		if (that.Card1 != _Empty)
			append="("+Card(that.Card1).str()+","+Card(that.Card2).str()+")";
		else
			append="(NULL,"+Card(that.Card2).str()+")";
		break;
	case CONNECT: 
		append="("+Card(that.Card1).str()+","+Card(that.Card2).str()+")";
		break;
	default:
		append="("+Card(that.Card1).str()+")";
	}
	switch(that.Action)
	{
	case FINISH:
		head="FINISH"; break;
	case POP:
		head="POP"; break;
	case DOWN:
		head="DOWN"; break;
	case CONNECT:
		head="CONNECT"; break;
	case MOVELINE:
		head="MOVELINE"; break;
	default:
		assert(false);
	}
	return(head+append);
}
int Tail(const vector<HistoryItem>& that)
{
	int ret=0;
	for (int i= that.size()-1; i>=0; i--)
	{
		if (that[i].Action==FINISH)
			++ret;
		else
			break;
	}
	return ret;
}
bool BetterHistoryItem(HistoryItem dst,HistoryItem src)
{
	if (dst.Action < src.Action)
		return true;
	else if (dst.Action > src.Action)
		return false;
	else
	{
		//在這裡確定dst.Action==src.Action
		switch(dst.Action)
		{
		case FINISH:  case POP: case DOWN:
			if (dst.Card1 > src.Card1)
				return true;
			else if (dst.Card1 < src.Card1)
				return false;
			else
				return(false);
			break;
		case CONNECT: 
			if (dst.Card1 > src.Card1)
				return true;
			else if (dst.Card1<src.Card1)
				return false;
			else  //這裡確定 dst.Card1==src.Card1
			{
				return (dst.Card2>src.Card2);
			}
			break;
		case MOVELINE:
			if (dst.Card1== _Empty && src.Card1== _Empty)
			{
				return (dst.Card2>src.Card2);
			}else if (dst.Card1== _Empty)
				return true;
			else if (src.Card1== _Empty)
				return false;
			else
			{
				if (dst.Card1 > src.Card1)
					return true;
				else if (dst.Card1 < src.Card1)
					return false;
				else  //在這裡確定 dst.Card1==src.Card1
				{
					return(dst.Card2 > src.Card2);
				}
			}
		}
	}
	assert(false);
	return false;
}
bool BetterHistoryEqualSize(const vector<HistoryItem>& dst,const vector<HistoryItem>& src)
{
	if (dst.size()!= src.size())  //不應該隨便比較大小不同的History
		return false;
	int dst_tail= Tail(dst);
	int src_tail= Tail(src);
	if (dst_tail > src_tail)
		return true;
	else if (dst_tail < src_tail)
		return false;
	else
	{
		//在這裡確定兩個History的Tail相同
		for (int i= src.size()-1-src_tail ; i>=0; i--)
		{
			if (BetterHistoryItem(dst[i], src[i]))
				return true;
			else if (BetterHistoryItem(src[i],dst[i]))
				return false;
			else
				continue;
		}
	}
	return false;
}

bool BetterHistoryArbitary(const vector<HistoryItem>& dst,const vector<HistoryItem>& src)
{
	//本函式只應用來比較兩個Complete World的歷程哪一個比較好
	if (dst.size() < src.size())
		return true;
	else if (dst.size() > src.size())
		return false;
	else
		return BetterHistoryEqualSize(dst,src);
}
bool EqualHistoryItem(HistoryItem a,HistoryItem b)
{
	if (a.Action == b.Action )
	{
		switch(a.Action)
		{
		case FINISH: case POP: case DOWN:
			return (a.Card1== b.Card1);
		case CONNECT: case MOVELINE:
			return (a.Card1==b.Card1 && a.Card2==b.Card2);
		default:
			return false;
		}
	}
	return false;
}
bool EqualHistoryVector(const vector<HistoryItem>& H1, const vector<HistoryItem>& H2)
{
	if (H1.size() != H2.size())
		return false;
	for (int i=0; i<H1.size(); i++)
	{
		if (!EqualHistoryItem(H1[i],H2[i]))
			return false;
	}
	return true;
}