

#ifndef U_H
#define U_H
#include "WorldExt.h" 

class U
{
private:
	vector<WorldExt> Data[22][22][5];
public:
	U();
private:
	bool SubExist(const vector<WorldExt>& V,const WorldExt& that) const;
public:
	int WorldNum() const;
	int WorldMax() const;
	void Clear();
	bool Add(WorldExt that);
	bool Exist(WorldExt that) const; 
	bool Remove(WorldExt that);
	WorldExt* EE(WorldExt inn);  ////'��J�@�ӧ�,�p�G���\���w�g�x�s�L�����A�⨺�ӧ��Ǧ^�ӡA�p�G�䤣��Ǧ^Null
	int Locate(WorldExt that) const;	
};

//static U  UOne;  //�n�����F

#endif