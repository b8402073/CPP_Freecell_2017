

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
	WorldExt* EE(WorldExt inn);  ////'輸入一個局,如果成功找到已經儲存過的局，把那個局傳回來，如果找不到傳回Null
	int Locate(WorldExt that) const;	
};

//static U  UOne;  //要拿掉了

#endif