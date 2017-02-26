
//#include <string>
//#include "card.h"
#include "HistoryItem.h"
//#include "Buffer.h"
//#include "Problem.h"
//#include "WorldExt.h"
#include "Sage.h"

static Card   _EX_MB[4]=  {Card(_Empty),Card(C5), Card(S12),Card(_Empty)};
static Buffer EX_BUFFER(_EX_MB);
static Card   _EX_ARR[8][21]={	{Card(H13),Card(C12),Card(H11),Card(C10),Card(H9),Card(S8),Card(D7) },  //7
								{Card(S13)},//1
								{Card(H2),Card(D6),Card(D5),Card(D11),Card(C2),Card(C8),Card(D9) },//7
								{Card(H8),Card(D13),Card(H5),Card(C4),Card(D3) },//5
								{Card(S10),Card(H7),Card(H3),Card(S11),Card(C6),Card(D10),Card(S9) },//7
								{Card(D12),Card(C11),Card(H10),Card(C9),Card(D8),Card(C7) },//6
								{Card(H12),Card(H4),Card(D2),Card(S6),Card(S4),Card(H6),Card(S5),Card(D4),Card(C3)},//9
								{Card(H1),Card(S7),Card(C13)}

};


//static byte _exarr[8]={7,1,7,5,7,6,9,3};
//static Problem EXAMPLE_PROBLEM(_EX_ARR,(byte[8]) {7,1,7,5,7,6,9,3},EX_BUFFER );  //C99的話可以這樣寫,但是VC不是C99
const static Problem EXAMPLE_PROBLEM(_EX_ARR, EX_BUFFER);

static Card    _MissionImpossible[8][21]={
	{Card(S1),Card(S10),Card(S12),Card(S7),Card(S4),Card(S9),Card(S2)},
	{Card(H1),Card(H10),Card(H12),Card(H7),Card(H4),Card(H9),Card(H2)},
	{Card(D1),Card(D10),Card(D12),Card(D7),Card(D4),Card(D9),Card(D2)},
	{Card(C1),Card(C10),Card(C12),Card(C7),Card(C4),Card(C9),Card(C2)},
	{Card(S3),Card(S8),Card(S5),Card(S6),Card(S11),Card(S13)},
	{Card(D3),Card(D8),Card(D5),Card(D6),Card(D11),Card(D13)},
	{Card(H3),Card(H8),Card(H5),Card(H6),Card(H11),Card(H13)},
	{Card(C3),Card(C8),Card(C5),Card(C6),Card(C11),Card(C13)}
};

const static Problem MissionImpossible(_MissionImpossible,Buffer());
//important part
#include "testStepByStep.h"

void TestWorld0_AutoSafeUp();
void TestWorld1_GetStrings();
void TestWorld2_StepByStep();
void TestWorld3_MoveLine();
void TestWorld4_About_NoAnswer();
void TestWorld5_MissionImpossible();
void TestWorld6_SageAboutExample();
void TestHistoryItem();
void TestBuffer();
void TestProblem();
void TestWorld();
void TestWorldExt();


void TestBeforeSage() 
{
	//TestWorld5_MissionImpossible();
	//TestWorld4_About_NoAnswer();
	TestWorld6_SageAboutExample();
}

int main()
{	
	cout<<_CardString[1] << _CardString[2]<<endl;
	
	cout<< EXAMPLE_PROBLEM.str() <<endl;

	//TestBuffer();
	//TestHistoryItem();
	//TestProblem();
	//TestWorld();
	//TestWorldExt();
	TestBeforeSage();
	getchar();
	return 0;
}
void TestProblem()
{
	cout<< EXAMPLE_PROBLEM.str() <<endl;
	for (int i=1; i<=8; i++)
	{
		cout<< (int) EXAMPLE_PROBLEM.GetNowMaxPos(i)<<" ";
		//sassert( EXAMPLE_PROBLEM.GetNowMaxPos(i)== _exarr[i-1] );		
	}
	cout<<"CardNum="<< EXAMPLE_PROBLEM.CardNum() <<endl;
	assert( EXAMPLE_PROBLEM.CardNum()==47 );

	NP Hello(EXAMPLE_PROBLEM);
	cout<< Hello.OutputArr.str() <<endl;
	vector<Card> vHello= Hello.getVector();
	NP::PrintVector(vHello);
	Problem restore= NP::BytesToProblem( NP::VectorToBytes(vHello));	
	cout<< restore.str() <<endl;
}
void TestBuffer()
{
	Buffer that;
	assert(that.GetSize()==0); 
	assert(that.Add(GetCard(10,CLUB))==true);
	assert(that.GetSize()==1);
	assert(that.Add(GetCard(8,SPADE))==true);
	assert(that.GetSize()==2);
	assert(that.Add(GetCard(8,SPADE))==false);
	assert(that.GetSize()==2);
	assert(that.Add(GetCard(6,HEART))==true);
	assert(that.GetSize()==3);
	assert(that.Add(GetCard(3,CLUB))==true);
	assert(that.GetSize()==4);
	assert(that.Add(GetCard(10,HEART))==false);
	assert(that.GetSize()==4);
	cout<< that.str() <<endl;
}
void TestHistoryItem()
{
	HistoryItem H1=ItemFinish(GetCard(2,CLUB));
	HistoryItem H2=ItemConnect(GetCard(2,HEART), GetCard(1,SPADE));
	HistoryItem H3=ItemPop(GetCard(13,HEART));
	HistoryItem H4=ItemDown(GetCard(12,SPADE));
	HistoryItem H5=ItemMoveLine(GetCard(8,SPADE), GetCard(6,SPADE));
	HistoryItem H6=ItemMoveLine(NULL,GetCard(7,DIAMOND));
	cout<< ItemToString(H1) <<endl;
	cout<< ItemToString(H2) <<endl;
	cout<< ItemToString(H3) <<endl;
	cout<< ItemToString(H4) <<endl;
	cout<< ItemToString(H5) <<endl;
	cout<< ItemToString(H6) <<endl;
	//HistoryItem X1=ItemConnect(GetCard(3,HEART), GetCard(1,SPADE));
	//HistoryItem X2=ItemMoveLine(GetCard(3,HEART), GetCard(8,SPADE));
}
void TestWorld()
{
	TestWorld0_AutoSafeUp();
	TestWorld1_GetStrings();
	TestWorld2_StepByStep();
	TestWorld3_MoveLine();
}

void TestWorld0_AutoSafeUp()
{

	static Card  _EX_ARR1_BUG[4]={ C6,D9,D10,C13};
	static Card  _EX_ARR2_BUG[8][21]= {
		{H13,C12,H11,C10,H9,C8},
		{S13},
		{S11},
		{H8,D13,H5},
		{S10,H7,H3},
		{D12,C11,H10,C9,D8,C7,H6},
		{H12,H4},
		{S12,D11}
	};


	static Problem EXAMPLE_BUG(_EX_ARR2_BUG, Buffer(_EX_ARR1_BUG));

	static Card _EX_ARR1_ANSWER[4]={D10,C13};
	static Card _EX_ARR2_ANSWER[8][21]={
		{H13,C12,H11,C10,H9},
		{S13},
		{S11},
		{H8,D13},
		{S10},
		{D12,C11,H10,C9},
		{H12},
		{S12,D11}
	};
	static Problem EXAMPLE_ANSWER(_EX_ARR2_ANSWER, Buffer(_EX_ARR1_ANSWER));
	
	World Test(EXAMPLE_BUG);
	Test.AutoSafeUp();
	World Ans(EXAMPLE_ANSWER);
	assert(Test.equals(&Ans));
	assert(Ans.equals(&Test));	
	cout<<"AutoSafeUp is OK"<<endl;
	cout<<"Test:"<<endl;
	cout<<Test.str()<<endl;
	cout<<"haha"<<endl;
}
void TestWorld1_GetStrings()
{
	cout<<"EXAMPLE_PROBLEM:"<<endl;
	cout<< EXAMPLE_PROBLEM.str() <<endl;
	World Test(EXAMPLE_PROBLEM);
	cout<<"Test:"<<endl;
	cout<< Test.str() <<endl;	
	cout<< Test.GetBufStrings()<<endl;
	assert(Test.GetBufStrings()=="5C,12S");
	cout<< Test.GetStrings(1)<<endl;
	assert(Test.GetStrings(1)=="3C,4D,5S,6H,4S,6S,2D,4H,12H");	
	cout<< Test.GetStrings(2)<<endl;
	assert(Test.GetStrings(2)=="7D,8S,9H,10C,11H,12C,13H");
	cout<< Test.GetStrings(3)<<endl;
	assert(Test.GetStrings(3)=="9S,10D,6C,11S,3H,7H,10S");
	cout<< Test.GetStrings(4)<<endl;
	assert(Test.GetStrings(4)=="9D,8C,2C,11D,5D,6D,2H");
	cout<< Test.GetStrings(5)<<endl;
	assert(Test.GetStrings(5)=="7C,8D,9C,10H,11C,12D");
	cout<< Test.GetStrings(6)<<endl;
	assert(Test.GetStrings(6)=="3D,4C,5H,13D,8H");
	cout<< Test.GetStrings(7)<<endl;
	assert(Test.GetStrings(7)=="13C,7S,1H");
	cout<< Test.GetStrings(8)<<endl;
	assert(Test.GetStrings(8)=="13S");

	
	World Complete(Problem(),Finisher(C13,D13,H13,S13));
	cout<< Complete.GetBufStrings()<<endl;
	assert(Complete.GetBufStrings()=="");
	cout<< Complete.GetStrings(1)<<endl;
	assert(Complete.GetStrings(1)=="");
	assert(Complete.GetStrings(2)=="");		
	assert(Complete.GetStrings(3)=="");
	assert(Complete.GetStrings(4)=="");
	assert(Complete.GetStrings(5)=="");
	assert(Complete.GetStrings(6)=="");
	assert(Complete.GetStrings(7)=="");
	assert(Complete.GetStrings(8)=="");

}

void TestWorld2_StepByStep()
{
	cout<< "Step By Step:"<<endl;
	World T(EXAMPLE_PROBLEM);

	Step01(T);	Step02(T);	Step03(T);	Step04(T);	Step05(T);

	Step06(T);  Step07(T);	Step08(T);	Step09(T);	Step10(T);

	Step11(T);	Step12(T);	Step13(T);	Step14(T);	Step15(T);

	Step16(T);  Step17(T); 	Step18(T);	Step19(T);	Step20(T);
	Step21(T);  Step22(T);	Step23(T);	Step24(T);	Step25(T);
	Step26(T);	Step27(T);	Step28(T);	Step29(T);	Step30(T);
	Step31(T);	Step32(T);	Step33(T);	Step34(T);	Step35(T);
	Step36(T);	Step37(T);	Step38(T);	Step39(T);	Step40(T);
	Step41(T);	Step42(T);	Step43(T);	Step44(T);	Step45(T);
	Step46(T);	Step47(T);	Step48(T);	Step49(T);	Step50(T);
	Step51(T);	Step52(T);	Step53(T);	Step54(T);	Step55(T);
	Step56(T);	Step57(T);	Step58(T);	Step59(T);	Step60(T);

}

void TestWorld3_MoveLine()
{
	World T(EXAMPLE_PROBLEM);
	Step01(T);
	
	cout<<"要確定MoveLine的時候不會整行抓掉到一個空行,以致雖然傳回true,NP卻不變"<<endl;
	cout<<endl<<"About T:"<<endl;
	cout<<T.str()<<endl;

	World Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(D7)));

/*
	cout<<"copy:"<<endl;
	cout<< Copy.str() << endl;

	PrintNP(Copy);
	NP that(Copy.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);
*/
	Card stream1[]={C5,S12,S13,_Empty,C3,S9,D9,C7,H9,D3,C13,D7,D4,D10,C8,D8,C10,C4,S7,S8,S5,C6,C2,C9,H11,H5,H1,_Empty,H6,S11,D11,H10,C12,D13,_Empty,S4,H3,D5,C11,H13,H8,_Empty,S6,H7,D6,D12,_Empty,D2,S10,H2,_Empty,H4,_Empty,H12,_EndOfStream};	
	assert ( checkGetBytes(Copy, ArrCardToVecCard(55,stream1) ) );

	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(D9)));
	assert(Copy.ValueEquals(&T));


	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(S9)));
	
	Card stream2[]={C5,S12,S13,_Empty,C3,D7,D9,C7,C6,D3,C13,S9,D4,S8,C8,D8,S11,C4,S7,D10,S5,H9,C2,C9,H3,H5,H1,_Empty,H6,C10,D11,H10,H7,D13,_Empty,S4,H11,D5,C11,S10,H8,_Empty,S6,C12,D6,D12,_Empty,D2,H13,H2,_Empty,H4,_Empty,H12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(55,stream2) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(C7)));

	Card stream3[]={C5,S12,S13,_Empty,C3,D7,S9,D9,D3,C9,C13,C7,D4,S8,D10,C8,C4,H10,S7,D8,S5,H9,C6,C2,H5,C11,H1,_Empty,H6,C10,S11,D11,D13,D12,_Empty,S4,H11,H3,D5,H8,_Empty,S6,C12,H7,D6,_Empty,D2,H13,S10,H2,_Empty,H4,_Empty,H12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(55,stream3) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(C3)));
	Card stream4[]={C5,S12,S13,_Empty,D7,S5,S9,D9,C7,D3,C13,C3,S8,H6,D10,C8,D8,C4,S7,D4,H9,S4,C6,C2,C9,H5,H1,_Empty,C10,S6,S11,D11,H10,D13,_Empty,H11,D2,H3,D5,C11,H8,_Empty,C12,H4,H7,D6,D12,_Empty,H13,H12,S10,H2,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(53,stream4) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(S9),Card(C7)));
	Card stream5[]={C5,S12,S13,_Empty,C3,C7,D7,D9,D3,C9,C13,_Empty,D4,D8,S8,C8,C4,H10,S7,_Empty,S5,S9,H9,C2,H5,C11,H1,_Empty,H6,D10,C10,D11,D13,D12,_Empty,S4,C6,H11,D5,H8,_Empty,S6,S11,C12,D6,_Empty,D2,H3,H13,H2,_Empty,H4,H7,_Empty,H12,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(57,stream5) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(D9),Card(D7)));

	Card stream6[]={C5,S12,S13,_Empty,C3,D7,S9,C7,H9,D3,C13,_Empty,D4,S8,D10,D8,C10,C4,S7,_Empty,S5,D9,C6,C9,H11,H5,H1,_Empty,H6,C8,S11,H10,C12,D13,_Empty,S4,C2,H3,C11,H13,H8,_Empty,S6,D11,H7,D12,_Empty,D2,D5,S10,_Empty,H4,D6,_Empty,H12,H2,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(57,stream6) ) );


	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(C5)));
	assert(Copy.ValueEquals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(S12)));
	assert(Copy.ValueEquals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(S13)));
	assert(Copy.ValueEquals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(S3)));
	assert(Copy.ValueEquals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(C13)));
	assert(Copy.ValueEquals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(H13)));
	assert(Copy.ValueEquals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(C1)));
	assert(Copy.ValueEquals(&T));
	assert(!Copy.MOVELINE(Card(C7),Card(C3)));
	assert(Copy.ValueEquals(&T));
	
	Step02(T);

	Copy=T;
	assert(Copy.MOVELINE(Card(D9),Card(D7)));
	Card streamB1[]={S12,S13,_Empty,C3,D7,S9,C7,H9,D3,C13,C5,D4,S8,D10,D8,C10,C4,S7,_Empty,S5,D9,C6,C9,H11,H5,H1,_Empty,H6,C8,S11,H10,C12,D13,_Empty,S4,C2,H3,C11,H13,H8,_Empty,S6,D11,H7,D12,_Empty,D2,D5,S10,_Empty,H4,D6,_Empty,H12,H2,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(56,streamB1) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(C5),Card(C3)));
	Card streamB2[]={S12,S13,_Empty,D7,S5,S9,D9,C7,D3,C3,C13,S8,H6,D10,C8,D8,C4,D4,S7,H9,S4,C6,C2,C9,H5,C5,H1,C10,S6,S11,D11,H10,D13,_Empty,H11,D2,H3,D5,C11,H8,_Empty,C12,H4,H7,D6,D12,_Empty,H13,H12,S10,H2,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(52,streamB2) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(S9),Card(C7)));


	Card streamB3[]={S12,S13,_Empty,C3,C7,D7,D9,D3,C9,C13,C5,D4,D8,S8,C8,C4,H10,S7,_Empty,S5,S9,H9,C2,H5,C11,H1,_Empty,H6,D10,C10,D11,D13,D12,_Empty,S4,C6,H11,D5,H8,_Empty,S6,S11,C12,D6,_Empty,D2,H3,H13,H2,_Empty,H4,H7,_Empty,H12,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(56,streamB3) ) );

	Copy=T;
	assert(!Copy.MOVELINE(Card(C7),Card(C3)));
	assert(!Copy.MOVELINE(Card(C5),Card(D3)));
	assert(!Copy.MOVELINE(Card(S9),Card(D7)));

	Step03(T);

	Copy=T;
	assert(!Copy.MOVELINE(Card(C5),Card(D3)));
	assert(!Copy.MOVELINE(Card(C7),Card(D4)));
	assert(T.equals(&Copy));
	assert(Copy.MOVELINE(Card(S9),Card(C7)));
	Card streamC1[]={C3,S12,S13,_Empty,C7,D4,D7,D9,D3,C9,C13,C5,D8,S5,S8,C8,C4,H10,S7,_Empty,S9,H6,H9,C2,H5,C11,H1,_Empty,D10,S4,C10,D11,D13,D12,_Empty,C6,S6,H11,D5,H8,_Empty,S11,D2,C12,D6,_Empty,H3,H4,H13,H2,_Empty,H7,H12,_Empty,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(56,streamC1) ) );

	Step04(T);

	Copy=T;
	assert(Copy.MOVELINE(Card(S9),Card(C7)));
	Card streamD1[]={C3,S12,S13,_Empty,C7,D7,S5,D9,D3,C9,C13,D4,D8,S8,H6,C8,C4,H10,S7,C5,S9,H9,S4,C2,H5,C11,H1,_Empty,D10,C10,S6,D11,D13,D12,_Empty,C6,H11,D2,D5,H8,_Empty,S11,C12,H4,D6,_Empty,H3,H13,H12,H2,_Empty,H7,_Empty,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(55,streamD1) ) );


	Copy=T;
	assert(Copy.MOVELINE(Card(C7),Card(S5)));
	Card streamD2[]={C3,S12,S13,_Empty,S5,D7,S9,D9,S4,D3,C13,D4,H6,S8,D10,C8,S6,C4,S7,C5,C7,H9,C6,C2,D2,H5,H1,_Empty,D8,C10,S11,D11,H4,D13,_Empty,C9,H11,H3,D5,H12,H8,_Empty,H10,C12,H7,D6,_Empty,C11,H13,S10,H2,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(54,streamD2) ) );

	Copy=T;
	assert(!Copy.MOVELINE(Card(D4),Card(C3)));
	assert(Copy.equals(&T)); assert(Copy.ValueEquals(&T));
	assert(!Copy.MOVELINE(Card(C13),Card(D12)));
	assert(Copy.equals(&T)); assert(Copy.ValueEquals(&T));

	Step05(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(D9),Card(D7)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(S9),Card(C7)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(C7),Card(H6)));
	assert(Copy.equals(&T));	
	assert(!Copy.MOVELINE(Card(C13),Card(C7)));
	assert(Copy.equals(&T));
	
	Step06(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(D9),Card(D7)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(S9),Card(H6)));
	assert(Copy.equals(&T));

	Step07(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(C13),Card(H6)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(H6),Card(D4)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(S6),Card(D3)));
	assert(Copy.equals(&T));

	Step08(T);
	Copy=T;
	assert(Copy.MOVELINE(Card(H6),Card(D4)));
	Card streamE1[]={C3,S12,S13,_Empty,D4,D7,S9,D9,D3,S6,C13,_Empty,C5,S8,D10,C8,C4,D2,S7,_Empty,H6,H9,C6,C2,H5,H4,H1,_Empty,C7,C10,S11,D11,D13,H12,_Empty,D8,H11,H3,D5,H8,_Empty,C9,C12,H7,D6,_Empty,H10,H13,S10,H2,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(55,streamE1) ) );
	
	Copy=T;
	assert(!Copy.MOVELINE(Card(S6),Card(D3)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(C13),Card(S6)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(C13),Card(H6)));
	assert(Copy.equals(&T));

	Step09(T);
	Copy=T;

	assert(Copy.MOVELINE(Card(H6),Card(D4)));
	Card streamF1[]={C3,S12,S13,_Empty,D4,D7,S9,D9,D3,D2,C13,_Empty,C5,S8,D10,C8,C4,H4,S7,_Empty,H6,H9,C6,C2,H5,H12,H1,_Empty,C7,C10,S11,D11,D13,_Empty,D8,H11,H3,D5,H8,_Empty,C9,C12,H7,D6,_Empty,H10,H13,S10,H2,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(54,streamF1) ) );
	
	Copy=T;
	assert(!Copy.MOVELINE(Card(C13),Card(S6)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(C13),Card(H6)));
	assert(Copy.equals(&T));

	Step10(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(D9),Card(D7)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(S7),Card(H6)));
	assert(Copy.equals(&T));

	Step11(T);
	Step12(T);
	Copy=T;
	assert(Copy.MOVELINE(Card(H6),Card(D4)));
	Card streamG1[]={C3,S12,C13,S13,_Empty,D4,D7,S9,D9,D3,D2,_Empty,C5,S8,D10,C8,C4,H4,_Empty,H6,H9,C6,C2,H5,H12,_Empty,C7,C10,S11,D11,D13,_Empty,D8,H11,H3,D5,H8,_Empty,C9,C12,H7,D6,_Empty,H10,H13,S10,H2,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(52,streamG1) ) );
	
	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(D7)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(D4)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(D9)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(D3)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(S9)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(H6)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(D2)));
	assert(Copy.equals(&T));

	Step13(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(D4)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(S9),Card(H6)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(D7)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(D9)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(D3)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(S9)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(H6)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(_Empty),Card(H4)));
	assert(Copy.equals(&T));

	Copy=T;
	assert(Copy.MOVELINE(Card(D9),Card(D7)));

	Card streamH1[]={C3,S12,C13,S13,_Empty,D7,H6,S9,H9,D3,H4,D4,_Empty,S8,C7,D10,C10,C4,H12,C5,_Empty,D9,D8,C6,H11,H5,_Empty,C8,C9,S11,C12,D13,_Empty,C2,H10,H3,H13,H8,_Empty,D11,C11,H7,_Empty,D5,D12,S10,_Empty,D6,_Empty,H2,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(51,streamH1) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(H6),Card(D4)));

	Card streamH2[]={C3,S12,C13,S13,_Empty,D4,D7,S9,D9,D3,H4,_Empty,C5,S8,D10,C8,C4,H12,_Empty,H6,H9,C6,C2,H5,_Empty,C7,C10,S11,D11,D13,_Empty,D8,H11,H3,D5,H8,_Empty,C9,C12,H7,D6,_Empty,H10,H13,S10,H2,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(51,streamH2) ) );

	Step14(T);
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step15(T);
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}

	Step16(T);
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}

	Step17(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(D11),Card(D7)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(S9),Card(H6)));
	assert(Copy.equals(&T));

	assert(Copy.MOVELINE(Card(H6),Card(D4)));

	Card streami1[]={S12,C13,S13,_Empty,D4,D7,S9,D3,D11,H4,C8,_Empty,C5,S8,D10,C4,D5,H12,D9,_Empty,H6,H9,C6,H5,D6,_Empty,C7,C10,S11,D13,H2,_Empty,D8,H11,H3,H8,_Empty,C9,C12,H7,_Empty,H10,H13,S10,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(49,streami1) ) );

	Step18(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(S9),Card(H6)));
	assert(Copy.equals(&T));
	assert(Copy.MOVELINE(Card(H6),Card(D4)));

	Card streamj1[]={S12,C13,S13,_Empty,D4,D7,S9,C4,D11,H4,C8,_Empty,C5,S8,D10,H5,D5,H12,D9,_Empty,H6,H9,C6,D13,D6,_Empty,C7,C10,S11,H8,H2,_Empty,D8,H11,H3,_Empty,C9,C12,H7,_Empty,H10,H13,S10,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(48,streamj1) ) );

	Step19(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(S9),Card(H6)));
	assert(Copy.equals(&T));

	Step20(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(S9),Card(H6)));
	assert(Copy.equals(&T));
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}

	Step21(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step22(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step23(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step24(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step25(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(C8)));
	assert(Copy.equals(&T));
	assert(Copy.MOVELINE(Card(_Empty),Card(H6)));

	Card streamk1[]={D11,S12,C13,S13,_Empty,D7,S9,D8,H5,H4,C8,H6,_Empty,S8,D10,C9,D13,H12,D9,C7,_Empty,H9,C6,H10,H8,_Empty,C10,S11,C11,_Empty,H11,H3,D12,_Empty,C12,H7,_Empty,H13,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(40,streamk1) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(S9)));

	Card streamk2[]={D11,S12,C13,S13,_Empty,D7,H6,C6,H5,H4,S9,C8,_Empty,S8,C7,S11,D13,H12,D10,D9,_Empty,H9,D8,H3,H8,_Empty,C10,C9,H7,_Empty,H11,H10,S10,_Empty,C12,C11,_Empty,H13,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(40,streamk2) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(D7)));

	Card streamk3[]={D11,S12,C13,S13,_Empty,H6,S9,H9,H5,H4,C8,D7,_Empty,C7,D10,C10,D13,H12,D9,S8,_Empty,D8,C6,H11,H8,_Empty,C9,S11,C12,_Empty,H10,H3,H13,_Empty,C11,H7,_Empty,D12,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(40,streamk3) ) );

	Step26(T);
	Copy=T;

	assert(!Copy.MOVELINE(Card(_Empty),Card(C8)));
	assert(Copy.equals(&T));
	assert(!Copy.MOVELINE(Card(S8),Card(C8)));
	assert(Copy.equals(&T));

	assert(Copy.MOVELINE(Card(S9),Card(H6)));

	Card streamL1[]={D11,S12,C13,S13,_Empty,H6,S8,C9,H5,H4,C8,_Empty,C7,H9,H10,D13,H12,D9,_Empty,D8,C10,C11,H8,_Empty,S9,H11,D12,_Empty,D10,C12,_Empty,C6,H13,_Empty,S11,_Empty,H3,_Empty,H7,_Empty,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(42,streamL1) ) );

	assert(Copy.MOVELINE(Card(_Empty),Card(H6)));
	Card streamL2[]={D11,S12,C13,S13,_Empty,D8,S8,C9,H5,H4,C8,H6,_Empty,S9,H9,H10,D13,H12,D9,C7,_Empty,D10,C10,C11,H8,_Empty,C6,H11,D12,_Empty,S11,C12,_Empty,H3,H13,_Empty,H7,_Empty,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(40,streamL2) ) );
	
	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(S9)));
	Card streamL3[]={D11,S12,C13,S13,_Empty,H6,S8,C6,H5,H4,S9,C8,_Empty,C7,H9,S11,D13,H12,D10,D9,_Empty,D8,C10,H3,H8,_Empty,C9,H11,H7,_Empty,H10,C12,S10,_Empty,C11,H13,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(39,streamL3) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(S8)));
	Card streamL4[]={D11,S12,C13,S13,_Empty,H6,S9,C10,H5,H4,S8,C8,_Empty,C7,D10,H11,D13,H12,H9,D9,_Empty,D8,C6,C12,H8,_Empty,C9,S11,H13,_Empty,H10,H3,_Empty,C11,H7,_Empty,D12,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(39,streamL4) ) );

	Step27(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(C8)));
	assert(!Copy.MOVELINE(Card(_Empty),Card(H5)));
	assert(!Copy.MOVELINE(Card(_Empty),Card(H4)));

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(H9)));
	Card streamM1[]={D11,S12,C13,S13,_Empty,H6,S9,H11,H5,H4,H9,C8,_Empty,C7,D10,C12,D13,H12,C10,D9,_Empty,D8,C6,H13,H8,_Empty,C9,S11,_Empty,H10,H3,_Empty,C11,H7,_Empty,D12,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(38,streamM1) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(S9)));
	Card streamM2[]={D11,S12,C13,S13,_Empty,H6,H9,C6,H5,H4,S9,C8,_Empty,C7,C10,S11,D13,H12,D10,D9,_Empty,D8,H11,H3,H8,_Empty,C9,C12,H7,_Empty,H10,H13,S10,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(38,streamM2) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(H6)));
	Card streamM3[]={D11,S12,C13,S13,_Empty,S9,H9,D8,H5,H4,C8,H6,_Empty,D10,C10,C9,D13,H12,D9,C7,_Empty,C6,H11,H10,H8,_Empty,S11,C12,C11,_Empty,H3,H13,D12,_Empty,H7,_Empty,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(38,streamM3) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(S9),Card(H6)));
	Card streamM4[]={D11,S12,C13,S13,_Empty,H6,H9,C9,H5,H4,C8,_Empty,C7,C10,H10,D13,H12,D9,_Empty,D8,H11,C11,H8,_Empty,S9,C12,D12,_Empty,D10,H13,_Empty,C6,_Empty,S11,_Empty,H3,_Empty,H7,_Empty,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(41,streamM4) ) );

	Step28(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(C8)));
	assert(!Copy.MOVELINE(Card(D10),Card(H6)));

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(H9)));
	Card streamN1[]={D11,S12,C13,S13,_Empty,H6,D10,H11,H5,H4,H9,C8,_Empty,C7,C6,C12,D13,H12,C10,D9,_Empty,D8,S11,H13,H8,_Empty,C9,H3,_Empty,H10,H7,_Empty,C11,S10,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(37,streamN1) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(H6)));
	Card streamN2[]={D11,S12,C13,S13,_Empty,D10,H9,D8,H5,H4,C8,H6,_Empty,C6,C10,C9,D13,H12,D9,C7,_Empty,S11,H11,H10,H8,_Empty,H3,C12,C11,_Empty,H7,H13,D12,_Empty,S10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(36,streamN2) ) );

	Step29(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(H9)));
	assert(!Copy.MOVELINE(Card(_Empty),Card(H6)));
	assert(!Copy.MOVELINE(Card(_Empty),Card(C8)));
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}

	Step30(T);
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}

	Step31(T);
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}

	Step32(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}

	Step33(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step34(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}

	Step35(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step36(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step37(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step38(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}
	Step39(T);
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				Copy=T;
				assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
				assert(Copy.equals(&T));
			}
		}
	}

	Step40(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(C8)));
	Copy=T;
	assert(Copy.MOVELINE(Card(D10),Card(C7)));
	Card streamP1[]={D11,S12,C13,S13,_Empty,H9,C7,H10,C8,D13,H12,_Empty,C10,D8,C11,D9,_Empty,H11,C9,D12,_Empty,C12,D10,_Empty,H13,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(26,streamP1) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(H9)));
	Card streamP2[]={D11,S12,C13,S13,_Empty,C7,H11,H9,C8,D13,H12,D10,_Empty,D8,C12,C10,D9,_Empty,C9,H13,_Empty,H10,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(27,streamP2) ) );

	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(C7)));
	Card streamP3[]={D11,S12,C13,S13,_Empty,H9,C9,C8,C7,D13,H12,D10,_Empty,C10,H10,D9,D8,_Empty,H11,C11,_Empty,C12,D12,_Empty,H13,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(26,streamP3) ) );

	Step41(T);
	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(H9)));
	Card streamQ1[]={D11,C13,S13,_Empty,C7,H9,C12,C8,D13,H12,D10,_Empty,D8,C10,H13,D9,_Empty,C9,H11,_Empty,H10,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(26,streamQ1) ) );
	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(C7)));
	Card streamQ2[]={D11,C13,S13,_Empty,H9,H10,C7,C8,D13,H12,D10,_Empty,C10,C11,D8,D9,_Empty,H11,D12,C9,_Empty,C12,_Empty,H13,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(25,streamQ2) ) );

	Step42(T);
	Copy=T;
	assert(Copy.MOVELINE(Card(H12),Card(C7)));
	Card streamR1[]={D11,C13,_Empty,C7,H9,C8,D13,D12,D10,_Empty,D8,C10,D9,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,H13,_Empty,H12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(25,streamR1) ) );
	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(H9)));
	Card streamR2[]={D11,C13,_Empty,C7,H9,C8,H13,D13,H12,D10,_Empty,D8,C10,D9,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(25,streamR2) ) );
	Copy=T;
	assert(Copy.MOVELINE(Card(D10),Card(C7)));
	Card streamR3[]={D11,C13,_Empty,H9,C7,H10,C8,D13,H12,_Empty,C10,D8,C11,D9,_Empty,H11,C9,D12,_Empty,C12,D10,_Empty,H13,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(24,streamR3) ) );	

	Step43(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(C10)));
	assert(Copy.equals(&T));
	Copy=T;
	assert(Copy.MOVELINE(Card(D13),Card(C10)));

	Card streamS1[]={D11,C13,_Empty,C7,C10,C8,H13,H12,D10,_Empty,D8,H11,D9,_Empty,C9,C12,_Empty,H10,D13,_Empty,C11,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(24,streamS1) ) );	
	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(C7)));
	Card streamS2[]={D11,C13,_Empty,C10,C7,C11,C8,D13,H12,D10,_Empty,H11,D8,D12,D9,_Empty,C12,C9,_Empty,H13,H10,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(22,streamS2) ) );	
	Copy=T;
	assert(Copy.MOVELINE(Card(C10),Card(C8)));
	Card streamS3[]={D11,C13,_Empty,C8,C7,D13,H12,D10,_Empty,D9,D8,_Empty,C10,C9,_Empty,H11,H10,_Empty,C12,C11,_Empty,H13,D12,_EndOfStream};	
	assert ( checkGetBytes(Copy, ArrCardToVecCard(22,streamS3) ) );	

	Step44(T);
	Copy=T;
	assert(!Copy.MOVELINE(Card(_Empty),Card(C10)));
	Copy=T;
	assert(Copy.MOVELINE(Card(_Empty),Card(D8)));
	Card streamT1[]={D11,C13,_Empty,C10,D8,C8,D13,H12,D12,D10,_Empty,H11,C9,D9,_Empty,C12,H10,_Empty,H13,C11,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(21,streamT1) ) );	

	Copy=T;
	assert(Copy.MOVELINE(Card(D10),Card(D8)));
	Card streamT2[]={D11,C13,_Empty,C10,H10,D8,C8,D13,H12,_Empty,H11,C11,C9,D9,_Empty,C12,D12,D10,_Empty,H13,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(21,streamT2) ) );	
	Copy=T;
	assert(Copy.MOVELINE(Card(C10),Card(C8)));

	Card streamT3[]={D11,C13,_Empty,C8,D8,D13,H12,D10,_Empty,D9,C9,_Empty,C10,H10,_Empty,H11,C11,_Empty,C12,D12,_Empty,H13,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(23,streamT3) ) );	
	Copy=T;
	assert(Copy.MOVELINE(Card(D13),Card(C10)));
	Card streamT4[]={D11,C13,_Empty,D8,C10,C8,H13,H12,D10,_Empty,C9,H11,D9,_Empty,H10,C12,_Empty,C11,D13,_Empty,D12,_EndOfStream};
	assert ( checkGetBytes(Copy, ArrCardToVecCard(22,streamT4) ) );	

	Step45(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				if ((i==5 && j==1) || (i==1 && j==8) ||
					(i==7 && j==6) )
					continue;
				else
				{
					Copy=T;
					assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
					assert(Copy.equals(&T));
				}
			}
		}
	}
	Step46(T);
	Copy=T;
	for (int i=1; i<=8; i++)
	{
		for (int j=1; j<=8; j++)
		{
			if (i!=j)
			{
				if ((i==7 && j==6) || (i==5 &&j==1) )
					continue;
				else
				{
					Copy=T;
					assert(!Copy.MOVELINE(Copy.P.Peek(i),Copy.P.Peek(j)));
					assert(Copy.equals(&T));
				}
			}
		}
	}
	//剩下的應該不用測了
	//Step47(T);
	//Copy=T;
	//Step48(T);
	//Copy=T;
	//Step49(T);
	//Copy=T;


///////
	
//	cout<<"copy:"<<endl;
//	cout<< Copy.str() << endl;

//	PrintNP(Copy);
//	NP that(Copy.P);
//	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
//	that.PrintVector(hand);		
///////

//	getchar();
}

void TestWorldExt()
{
	WorldExt PTT(EXAMPLE_PROBLEM);
	PTT.POP(S13);
	assert( PTT.MOVELINE(Card(S9),Card(C7)));
	assert( PTT.MOVELINE(Card(C9),Card(C7)));
	assert( !PTT.MOVELINE(Card(S9),Card(C7)));
	PTT=WorldExt(EXAMPLE_PROBLEM);
	PTT.POP(S13);
	assert( PTT.MOVELINE(Card(_Empty),Card(C7)));
	assert( PTT.MOVELINE(Card(C9),Card(C7)));
	assert( !PTT.MOVELINE(Card(_Empty),Card(C7)));


	WorldExt TT(EXAMPLE_PROBLEM);
	Step01(TT);
	WorldExt Copy=TT;
	//cout<< Copy.str() <<endl;
	assert(!Copy.DOWN(Card(S13)));
	assert(Copy.equals(&TT));
	World X=Copy;
	assert(EqualHistoryItem( X.History[ X.History.size()-1 ], ItemPop(Card(S13))));
	Step02(TT);
	Copy=TT;
	assert(!Copy.POP(C5));
	assert(Copy.equals(&TT));
	X=Copy;
	assert(EqualHistoryItem( X.History[ X.History.size()-1 ], ItemDown(Card(C5))));	
	Step03(TT);
	Copy=TT;
	assert(!Copy.DOWN(C3));
	X=Copy;
	assert(EqualHistoryItem( X.History[ X.History.size()-1 ], ItemPop(C3) ));
	Step04(TT);
	Copy=TT;
	cout<< TT.str() <<endl;
	assert(Copy.CONNECT(S5,D4));
	assert(!Copy.CONNECT(C5,D4));
	X=TT;
	assert(EqualHistoryItem( X.History[ X.History.size()-1 ], ItemConnect(C5,D4) ));
	Step05(TT);
	Copy=TT;
	assert(!Copy.DOWN(S5));
	assert(Copy.equals(&TT));
	X=Copy;
	assert(EqualHistoryItem( X.History[ X.History.size()-1 ], ItemPop(S5) ));

	Step06(TT);
	Copy=TT;
	cout<< TT.str() <<endl;

	WorldExt Left(EXAMPLE_PROBLEM),Right(EXAMPLE_PROBLEM);
	Left.POP(D9);
	cout<<"Left:"<<endl;
	cout<< Left.str() <<endl;

	Right.MOVELINE(Card(S9),Card(C7));
	cout<<"Right:"<<endl;
	cout<<Right.str()<<endl;
	
	vector<WorldExt> what;
	what.push_back(Left);
	what.push_back(Right);
	std::sort( what.begin(), what.end(), World::CardNum_TotalAV);

	cout<<"2017/01/31:"<<endl;
	cout<<"以前的設計，關於WorldExt::POP_N(int Line,int N)這個東西有很大的錯誤："<<endl;
	cout<<"雖然這個東西的好處可以讓解趕快產生"<<endl;
	cout<<"基本上這個東西不應該存在,因為這樣會讓局面的演變變得很亂"<<endl;
	cout<<"再加上在這裡有ReserveWorld()/ResumeWorld()的呼叫，會跟底下的_DOWN()裡面的ReserveWorld()/ResumeWorld()弄亂掉"<<endl;
	cout<<"所以今天做一個設計決定:"<<endl;
	cout<<"移除POP_N(int Line,int N)然後把WorldExt::makeChild5()重寫"<<endl;
	cout<<"但是剛剛想一下，POP_N可以用在MakeStone的步驟歐....."<<endl;

	cout<<"2017/02/01"<<endl;
	cout<<"POP_N(int Line,int N)雖然可以用在MakeStone的步驟，但是這個動作可以用'makeChild連續做4次來代替'"<<endl;

	cout<<"2017/02/04"<<endl;
	cout<<"加入NoAnswer全域變數,以後RightFS如果沒有找到答案就傳回NoAnswer"<<endl;

	cout<<"2017/02/05"<<endl;
	cout<<"https://github.com/b8402073/CPP_Freecell_2017.git"<<endl;

	//getchar();
}


void TestWorld4_About_NoAnswer()
{
	//about NoAnswer
	World T(EXAMPLE_PROBLEM);
	assert(!T.FINISH(H1));
	assert(sizeof(WorldExt::NoAnswer)>0);
	assert(WorldExt::NoAnswer.P.CardNum()>0);
	assert(!WorldExt::NoAnswer.isComplete());
	assert(!T.equals(&WorldExt::NoAnswer));
	assert(WorldExt::NoAnswer.equals(&WorldExt::NoAnswer));


}
void TestWorld5_MissionImpossible()
{	
	cout<<"TestWorld5_MissionImpossible:"<<endl;
	WorldExt H(MissionImpossible);	
	cout<<"MissionImposible:"<<endl;
	cout<< H.str()<<endl;
	Sage S(H);
	assert(S.Stone.size()==12);
	cout<<"S.Stone.size()="<<S.Stone.size()<<endl;
	S.Run1(true);


}

void TestWorld6_SageAboutExample()
{
	/*
	WorldExt H(EXAMPLE_PROBLEM);
	cout<< H.str()<<endl;
	Sage S(H);
	assert(S.Stone.size()==3435);
	cout<<"S.Stone.size()="<<S.Stone.size()<<endl;
	S.Run1(true);
	cout<< S.Result.str()<<endl;
	*/

	WorldExt H(EXAMPLE_PROBLEM);
	H.POP(S13);
	WorldExt K=H;
	cout<<"K:"<<endl;
	cout<< K.str()<<endl;

	WorldExt A(EXAMPLE_PROBLEM);
	Sage P(A);
	P.Run2(true);
	cout<< P.Result.str();
}