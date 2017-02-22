/**
À£¤O´ú¸Õ¥Î
*/

#include "WorldExt.h"
#include "Sage.h"
#include "testStepByStep.h"
using namespace std;
int main()
{
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
	cout<<"No Answer:"<<endl;
	cout<< WorldExt::NoAnswer.str()<<endl;
	cout<<"NoAnswer.equals(&NoAnswer)="<<  WorldExt::NoAnswer.equals( &WorldExt::NoAnswer) <<endl;

	const static Problem EXAMPLE_PROBLEM(_EX_ARR, EX_BUFFER);

	WorldExt what(EXAMPLE_PROBLEM);
	assert(what.POP(S13));
	assert(what.POP(D7));
	assert(what.DOWN(S8));

	WorldExt T(EXAMPLE_PROBLEM);
	cout<< T.str()<<endl;
	/*
	Step01(T);	Step02(T);	Step03(T);	Step04(T);	Step05(T);

	Step06(T);  Step07(T);	Step08(T);	Step09(T);	Step10(T);

	Step11(T);	Step12(T);	Step13(T);	Step14(T);	Step15(T);

	Step16(T);  Step17(T); 	Step18(T);	Step19(T);	Step20(T);
	Step21(T);  Step22(T);	Step23(T);	Step24(T);	Step25(T);
	Step26(T);	Step27(T);	Step28(T);	Step29(T);	Step30(T);
	//Step31(T);	Step32(T);	Step33(T);	Step34(T);	Step35(T);
	//Step36(T);	Step37(T);	Step38(T);	Step39(T);	Step40(T);
	//Step41(T);	Step42(T);	Step43(T);	Step44(T);	Step45(T);
	*/


	Sage PPP(T);
	assert(PPP.Stone.size()>400);
	if (PPP.Run2(true))
	{
		cout<<endl<<"Run2 SOLUTION"<<endl;
		cout<< PPP.Result.str() <<endl;
	}else
		cout<<"Found no solution"<<endl;
	
	/*
	for (int i=1; i<=100; i++)
	{
		WorldExt that=WorldExt(Problem(i));
		cout<< that.str()<<endl;
		Sage PPP(that);
		cout<< PPP.root.str()<<endl;
		PPP.Run1(true);		
		cout<< PPP.Result.str()<<endl;		
		//cout<<"Found no solution"<<endl;
		UOne.Clear();
	}
	*/

	getchar();
	return 0;
}
