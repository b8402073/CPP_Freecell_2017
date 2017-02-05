#include "Buffer.h"
Buffer::Buffer()
:size(0)
{
}

Buffer::Buffer(const Card inn[4]) 
{
	std::copy(inn, inn+4, mydata);
	sort();
}
Buffer::Buffer(const Buffer &inn)
{
	std::copy(inn.mydata,inn.mydata+4,mydata);
	sizeupdate();
}

void Buffer::sizeupdate() 
{
	size=0;
	for (byte i=0; i<4; i++)
	{
		if (mydata[i]>0)
			size++;
		else
			break;
	}
}
void Buffer::sort()
{
	struct 
	{
		bool operator()(Card prev,Card next)
		{	
			
			if (prev==0 && next>0)
				return false;
			else if (prev==next)
				return false;		//如果測試跑不過要改這行
			else if (prev>=0 && next==0)
				return true;
			return (prev<next);			
		}
	}BufferSortCard;
	std::sort(mydata,mydata+4,BufferSortCard);
	sizeupdate();
}
/*
Card Buffer::get(byte pos) const
{
	assert(pos>=0 && pos<4);
	return mydata[pos];	
}
*/

int Buffer::Search(Card that) const
{
	for (byte i=0; i<size; i++)
	{
		if (that==mydata[i])
			return i;
	}
	return (-1);
}
bool Buffer::Add(Card that) 
{
	if (that!=0)
	{
		if (Available()>0 &&Search(that)<0)
		{
			mydata[size]=that;
			sort();
			return true;
		}	
	}
	return false;
}
bool Buffer::Remove(Card that)
{
	if (that!=0)
	{
		if (size>=1)
		{
			byte i=Search(that);
			if (i>=0)
			{
				mydata[i]=_Empty;
				sort();
				return true;
			}
		}
	}
	return false;
}
string Buffer::str() const
{
	string ret="[";
	for (byte i=0; i<3; i++)
	{
		assert(mydata[i]>=0);
		string str;
		if (mydata[i]>0)
			str=mydata[i].str();
		else
			str="EMPTY";
		ret.append(str+",");
	}
	ret.append(mydata[3]>0 ? mydata[3].str() : "EMPTY" );
	ret.append("]");
	return ret;
}
Buffer* Buffer::copy() const
{
	Buffer* ret=new Buffer(mydata);
	return ret;
}
bool Buffer::equals(const Buffer* that) const
{
	if (size!=that->size)
		return false;
	return( mydata[0]== that->mydata[0] &&
		    mydata[1]== that->mydata[1] &&
			mydata[2]== that->mydata[2] && 
			mydata[3]== that->mydata[3] );
}
vector<Card> Buffer::toVector() const
{
	vector<Card> ret;
	for (int i=0; i<size; i++)
	{
		ret.push_back(mydata[i]);
	}
	return ret;
}