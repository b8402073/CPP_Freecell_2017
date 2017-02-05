#include <vector>
#include <algorithm>
#include "card.h"

#ifndef BUFFER_H
#define BUFFER_H
class Buffer
{
private:
	Card mydata[4];
	byte size;
	void sizeupdate();
	void sort();
public:
	Buffer();
	Buffer(const Card inn[4]);
	Buffer(const Buffer& inn);
	inline int GetSize() const { return size; }
	inline Card get(byte pos) const {assert(pos>=0 && pos<4);return mydata[pos];}
	int Search(Card that) const;  //�n�`�N�o�̶Ǧ^�Ȫ��N���F
	bool Add(Card that);
	bool Remove(Card that);
	byte Available() const { return 4-size;}
	string str() const;
	Buffer* copy() const;
	bool equals(const Buffer* that) const;
	vector<Card> toVector() const;
};
#endif
