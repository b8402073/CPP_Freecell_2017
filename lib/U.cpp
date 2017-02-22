#include "U.h"
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
