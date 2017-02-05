#include <vector>
#include "card.h"
#ifndef HISTORY_H
#define HISTORY_H
enum ACTION_TYPE {FINISH=0,POP=1,DOWN=2,CONNECT=3,MOVELINE=4};
typedef struct _HistoryItem  
{
	unsigned int Action: 4;
	unsigned int Card1:  6;
	unsigned int Card2:  6;	
}HistoryItem;

HistoryItem ItemFinish(Card that);
HistoryItem ItemPop(Card that);
HistoryItem ItemDown(Card that);
HistoryItem ItemConnect(Card C1,Card C2);
HistoryItem ItemMoveLine(Card C1,Card C2);
string      ItemToString(HistoryItem that);
bool		EqualHistoryItem(HistoryItem a, HistoryItem b);

int			Tail(const vector<HistoryItem>& that);
bool		BetterHistoryItem(HistoryItem H1,HistoryItem H2);
bool		BetterHistoryEqualSize(const vector<HistoryItem>& dst,const vector<HistoryItem>& src);

bool		BetterHistoryArbitary(const vector<HistoryItem>& dst ,const vector<HistoryItem>& src);/*本函式只應用來比較兩個Complete World的歷程哪一個比較好*/

#endif
