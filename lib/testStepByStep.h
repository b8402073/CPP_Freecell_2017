bool checkGetBytes(const World& W, vector<Card> Given)
{
	Card* hand=(Card*) W.P.getBytes();
	//assert( hand[  Given.size()-1 ] == _EndOfStream );
	for (int i=0; i<Given.size(); i++)
	{
//#define SHOWI		
#if defined(SHOWI)
		cout<<"i="<<i<<"->"<<hand[i].str();
#endif
		assert( hand[i]==  Given[i] );
	}
	cout << "ByteArr of Step"<< W.History.size() << "is OK";

	Problem back= NP::BytesToProblem((byte*) hand);
	assert( W.P.ValueEquals(&back));
	assert( back.ValueEquals(&(W.P)));
	delete[] hand;
	return true;
}
vector<Card> ArrCardToVecCard(int sz,Card arr[])
{
	vector<Card> ret;
	for (int i=0; i<sz; i++)
	{
		ret.push_back(arr[i]);
	}
	return ret;
}
/*
//這個是模板,希望大家都照這樣寫
void StepXX(World& T)
{
	World Old=T;
	assert(T.XXX);
	int arr[]={0,0,0,0,0,0,0,0};
	assert( CheckNowMaxPos(T,arr,"XX"));
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	//some other verification
	assert(T.P.SearchBuffer(C5)<0);	

	//some HistoryItem verification
	assert(T.History.size()==5);
	assert(T.History[T.History.size()-1].Action==POP);
	assert(T.History[T.History.size()-1].Card1==S5);	


	//print NP and P
	PrintP(T);
	PrintNP(T);

	//這一段要印getBytes()應該有的值
	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ _EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(1,stream) ) );

}
*/
void PrintNP(const World& W)
{
	cout<<"NP of T"<<endl;
	NP MyNP(W.P);
	cout<< MyNP.str()<<endl; 
}
void PrintP(const World& W)
{
	cout<< W.str()<<endl;
}

bool CheckNowMaxPos(const World& W, int given[],string step)
{
	for (int i=1; i<=8; i++)
	{
		int left=W.P.GetNowMaxPos(i);
		if	(left!=given[i-1])
		{
			cout<<"Step"<<step<<"(CheckNowMaxPos):"<<endl;
			assert(false);
		}
	}
	return true;
}
void Step01(World& T);
void Step02(World& T);
void Step03(World& T);
void Step04(World& T);
void Step05(World& T);
void Step06(World& T);
void Step07(World& T);
void Step08(World& T);
void Step09(World& T);
void Step10(World& T);
void Step11(World& T);
void Step12(World& T);
void Step13(World& T);
void Step14(World& T);
void Step15(World& T);
void Step16(World& T);
void Step17(World& T);
void Step18(World& T);
void Step19(World& T);
void Step20(World& T);
void Step21(World& T);
void Step22(World& T);
void Step23(World& T);
void Step24(World& T);
void Step25(World& T);
void Step26(World& T);
void Step27(World& T);
void Step28(World& T);
void Step29(World& T);
void Step30(World& T);
void Step31(World& T);
void Step32(World& T);
void Step33(World& T);
void Step34(World& T);
void Step35(World& T);
void Step36(World& T);
void Step37(World& T);
void Step38(World& T);
void Step39(World& T);
void Step40(World& T);
void Step41(World& T);
void Step42(World& T);
void Step43(World& T);
void Step44(World& T);
void Step45(World& T);
void Step46(World& T);
void Step47(World& T);
void Step48(World& T);
void Step49(World& T);
void Step50(World& T);
void Step51(World& T);
void Step52(World& T);
void Step53(World& T);
void Step54(World& T);
void Step55(World& T);
void Step56(World& T);
void Step57(World& T);
void Step58(World& T);
void Step59(World& T);
void Step60(World& T);

void Step01(World& T)
{
	World Old=T;
	assert(T.POP(S13));
	int arr[]={6,-1,6,4,6,5,8,2};
	assert( CheckNowMaxPos(T, arr,"01") );
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	assert(T.P.PeekBuffer(2)==S13);


	//assert History
	assert(T.History.size()==1);
	assert(T.History[0].Action==POP);
	assert(T.History[0].Card1==S13);
	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);
	

	Card stream[]={C5,S12,S13,_Empty,C3,D7,S9,D9,C7,D3,C13,_Empty,
				D4,S8,D10,C8,D8,C4,S7,_Empty,
				S5,H9,C6,C2,C9,H5,H1,_Empty,
				H6,C10,S11,D11,H10,D13,_Empty,
				S4,H11,H3,D5,C11,H8,_Empty,
				S6,C12,H7,D6,D12,_Empty,
				D2,H13,S10,H2,_Empty,
				H4,_Empty,
				H12,_EndOfStream};
	

	assert ( checkGetBytes(T, ArrCardToVecCard(57,stream) ) );


}
void Step02(World& T)
{
	World Old=T;
	assert(T.DOWN(C5));
	int arr[]={6,0,6,4,6,5,8,2};
	assert( CheckNowMaxPos(T, arr,"02") );
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	assert(T.P.SearchBuffer(C5)<0);	

	assert(T.History.size()==2);
	assert(T.History[1].Action==DOWN);
	assert(T.History[1].Card1==C5);

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

	
	Card stream[]={S12,S13,_Empty,C3,D7,S9,D9,C7,D3,C13,C5,D4,S8,D10,C8,D8,C4,S7,_Empty,S5,H9,C6,C2,C9,H5,H1,_Empty,H6,C10,S11,D11,H10,D13,_Empty,S4,H11,H3,D5,C11,H8,_Empty,S6,C12,H7,D6,D12,_Empty,D2,H13,S10,H2,_Empty,H4,_Empty,H12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(56,stream) ) );


}

void Step03(World& T)
{
	World Old=T;
	assert(T.POP(C3));
	int arr[]={6,0,6,4,6,5,7,2};
	assert( CheckNowMaxPos(T,arr,"03"));
	assert(Old.GetStrings(1)!=T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	//some other verification
	assert(T.P.SearchBuffer(C3)==0);	

	PrintP(T);
	PrintNP(T);

	assert(T.History.size()==3);
	assert(T.History[2].Action==POP);
	assert(T.History[2].Card1==C3);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);


	Card stream[]={C3,S12,S13,_Empty,D4,D7,S9,D9,C7,D3,C13,C5,S5,S8,D10,C8,D8,C4,S7,_Empty,H6,H9,C6,C2,C9,H5,H1,_Empty,S4,C10,S11,D11,H10,D13,_Empty,S6,H11,H3,D5,C11,H8,_Empty,D2,C12,H7,D6,D12,_Empty,H4,H13,S10,H2,_Empty,H12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(55,stream) ) );


}

void Step04(World& T)
{
	World Old=T;
	assert(T.CONNECT(C5,D4));
	int arr[]={6,1,6,4,6,5,6,2};
	assert( CheckNowMaxPos(T,arr,"04"));
	assert(Old.GetStrings(2)==T.GetStrings(1));
	assert(Old.GetStrings(1)!=T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	//some other verification
	assert(T.P.Peek(2)==D4);
	assert(T.P.Peek(7)==S5);

	assert(T.History.size()==4);
	assert(T.History[T.History.size()-1].Action==CONNECT);
	assert(T.History[T.History.size()-1].Card1==C5);
	assert(T.History[T.History.size()-1].Card2==D4);

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

	Card stream[]={C3,S12,S13,_Empty,D7,S5,S9,D9,C7,D3,C13,D4,S8,H6,D10,C8,D8,C4,S7,C5,H9,S4,C6,C2,C9,H5,H1,_Empty,C10,S6,S11,D11,H10,D13,_Empty,H11,D2,H3,D5,C11,H8,_Empty,C12,H4,H7,D6,D12,_Empty,H13,H12,S10,H2,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(53,stream) ) );


}
void Step05(World& T)
{
	World Old=T;
	assert(T.POP(S5));
	int arr[]={6,1,6,4,6,5,5,2};
	assert( CheckNowMaxPos(T,arr,"05"));
	//PrintNP(T);
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(3)==T.GetStrings(2));
	assert(Old.GetStrings(4)==T.GetStrings(3));
	assert(Old.GetStrings(4)!=T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	//some other verification
	assert(T.P.SearchBuffer(S5)==1);	

	assert(T.History.size()==5);
	assert(T.History[T.History.size()-1].Action==POP);
	assert(T.History[T.History.size()-1].Card1==S5);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

	


	Card stream[]={C3,S5,S12,S13,_Empty,D7,S9,D9,H6,C7,D3,C13,D4,S8,D10,C8,S4,D8,C4,S7,C5,H9,C6,C2,S6,C9,H5,H1,_Empty,C10,S11,D11,D2,H10,D13,_Empty,H11,H3,D5,H4,C11,H8,_Empty,C12,H7,D6,H12,D12,_Empty,H13,S10,H2,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(53,stream) ) );

}

void Step06(World& T)
{
	World Old=T;
	assert(T.CONNECT(C7,H6));
	int arr[]={6,1,6,4,6,6,4,2};
	assert( CheckNowMaxPos(T,arr,"06"));
	//PrintNP(T);
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(3));
	assert(Old.GetStrings(3)==T.GetStrings(4));
	assert(Old.GetStrings(4)!=T.GetStrings(5));
	assert(Old.GetStrings(5)!=T.GetStrings(4));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	//some other verification
	assert(T.P.Peek(6)==H6);
	assert(T.P.Peek(7)==S4);

	//some HistoryItem verification
	assert(T.History.size()==6);
	assert(T.History[T.History.size()-1].Action==CONNECT);
	assert(T.History[T.History.size()-1].Card1==C7);	
	assert(T.History[T.History.size()-1].Card2==H6);	


	//print NP and P
	PrintP(T);
	PrintNP(T);
	
	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

	Card stream[]={C3,S5,S12,S13,_Empty,D7,H6,S9,D9,S4,D3,C13,D4,S8,C7,D10,C8,S6,C4,S7,C5,H9,D8,C6,C2,D2,H5,H1,_Empty,C10,C9,S11,D11,H4,D13,_Empty,H11,H10,H3,D5,H12,H8,_Empty,C12,C11,H7,D6,_Empty,H13,D12,S10,H2,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(53,stream) ) );

}
void Step07(World& T)
{
	World Old=T;
	assert(T.FINISH(S4));
	int arr[]={6,1,6,4,6,6,3,2};
	assert( CheckNowMaxPos(T,arr,"07"));
	PrintNP(T);
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)!=T.GetStrings(6));
	assert(Old.GetStrings(6)==T.GetStrings(5));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));

	cout<< Old.GetBufStrings()<<endl;
	cout<< T.GetBufStrings()<<endl;


	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(7)==S6);
	
	//some HistoryItem verification
	assert(T.History.size()==7);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S4);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

	
	Card stream[]={C3,S5,S12,S13,_Empty,D7,H6,S9,D9,D3,S6,C13,D4,S8,C7,D10,C8,C4,D2,S7,C5,H9,D8,C6,C2,H5,H4,H1,_Empty,C10,C9,S11,D11,D13,H12,_Empty,H11,H10,H3,D5,H8,_Empty,C12,C11,H7,D6,_Empty,H13,D12,S10,H2,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(52,stream) ) );

}
void Step08(World& T)
{
	World Old=T;
	assert(T.FINISH(S5));
	int arr[]={6,1,6,4,6,6,3,2};
	assert( CheckNowMaxPos(T,arr,"08"));
	PrintNP(T);
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()!=T.GetBufStrings());
	
	//some other verification
	assert(T.P.SearchBuffer(S5)==-1);
	
	//some HistoryItem verification
	assert(T.History.size()==8);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S5);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

	Card stream[]={C3,S12,S13,_Empty,D7,H6,S9,D9,D3,S6,C13,D4,S8,C7,D10,C8,C4,D2,S7,C5,H9,D8,C6,C2,H5,H4,H1,_Empty,C10,C9,S11,D11,D13,H12,_Empty,H11,H10,H3,D5,H8,_Empty,C12,C11,H7,D6,_Empty,H13,D12,S10,H2,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(51,stream) ) );


}
void Step09(World& T)
{
	World Old=T;
	assert(T.FINISH(S6));
	int arr[]={6,1,6,4,6,6,2,2};
	assert( CheckNowMaxPos(T,arr,"09"));
	//PrintNP(T);
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)!=T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(7)==D2);
	
	//some HistoryItem verification
	assert(T.History.size()==9);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S6);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

	Card stream[]={C3,S12,S13,_Empty,D7,H6,S9,D9,D3,D2,C13,D4,S8,C7,D10,C8,C4,H4,S7,C5,H9,D8,C6,C2,H5,H12,H1,_Empty,C10,C9,S11,D11,D13,_Empty,H11,H10,H3,D5,H8,_Empty,C12,C11,H7,D6,_Empty,H13,D12,S10,H2,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(50,stream) ) );

}
void Step10(World& T)
{
	World Old=T;
	assert(T.POP(C13));
	int arr[]={6,1,6,4,6,6,2,1};
	assert( CheckNowMaxPos(T,arr,"10"));
	PrintNP(T);
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)!=T.GetStrings(8));
	assert(Old.GetStrings(8)==T.GetStrings(7));
	assert(Old.GetBufStrings()!=T.GetBufStrings());
	
	//some other verification
	assert(T.P.SearchBuffer(C13)==2);
	
	//some HistoryItem verification
	assert(T.History.size()==10);
	assert(T.History[T.History.size()-1].Action==POP);
	assert(T.History[T.History.size()-1].Card1==C13);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

	Card stream[]={C3,S12,C13,S13,_Empty,D7,H6,S9,D9,D3,D2,D4,S7,S8,C7,D10,C8,C4,H4,C5,H1,H9,D8,C6,C2,H5,H12,_Empty,C10,C9,S11,D11,D13,_Empty,H11,H10,H3,D5,H8,_Empty,C12,C11,H7,D6,_Empty,H13,D12,S10,H2,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(50,stream) ) );

}


void Step11(World& T)
{
	World Old=T;
	assert(T.FINISH(S7));
	int arr[]={6,1,6,4,6,6,2,0};
	assert( CheckNowMaxPos(T,arr,"11"));
	PrintNP(T);
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(8)==H1);
	
	//some HistoryItem verification
	assert(T.History.size()==11);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S7);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

	Card stream[]={C3,S12,C13,S13,_Empty,D7,H6,S9,D9,D3,D2,D4,H1,S8,C7,D10,C8,C4,H4,C5,_Empty,H9,D8,C6,C2,H5,H12,_Empty,C10,C9,S11,D11,D13,_Empty,H11,H10,H3,D5,H8,_Empty,C12,C11,H7,D6,_Empty,H13,D12,S10,H2,_EndOfStream};	
	assert ( checkGetBytes(T, ArrCardToVecCard(50,stream) ) );


}


void Step12(World& T)
{
	World Old=T;
	assert(T.FINISH(H1));
	int arr[]={6,1,6,4,6,6,2,-1};
	assert( CheckNowMaxPos(T,arr,"12"));
	//PrintNP(T);
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(8)==_Empty);
	assert(T.P.FirstBlankLine()==8);
	
	//some HistoryItem verification
	assert(T.History.size()==12);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H1);	

	//print NP and P
	PrintP(T);
	PrintNP(T);


	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);


	Card stream[]={C3,S12,C13,S13,_Empty,D7,H6,S9,D9,D3,D2,D4,_Empty,S8,C7,D10,C8,C4,H4,C5,_Empty,H9,D8,C6,C2,H5,H12,_Empty,C10,C9,S11,D11,D13,_Empty,H11,H10,H3,D5,H8,_Empty,C12,C11,H7,D6,_Empty,H13,D12,S10,H2,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(50,stream) ) );


}


void Step13(World& T)
{
	World Old=T;
	assert(T.FINISH(D2));
	int arr[]={6,1,6,4,6,6,1,-1};
	assert( CheckNowMaxPos(T,arr,"13"));
	//PrintNP(T);
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)!=T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(7)==H4);
	assert(T.P.FirstBlankLine()==8);
	assert(T.P.BlankLine().size()==1);
	
	//some HistoryItem verification
	assert(T.History.size()==13);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D2);	

	//print NP and P
	PrintP(T);
	PrintNP(T);


	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);
//size=49[C3,S12,C13,S13,_Empty,D7,H6,S9,D9,D3,H4,D4,_Empty,S8,C7,D10,C8,C4,H12,C5,_Empty,H9,D8,C6,C2,H5,_Empty,C10,C9,S11,D11,D13,_Empty,H11,H10,H3,D5,H8,_Empty,C12,C11,H7,D6,_Empty,H13,D12,S10,H2,_EndOfStream]

	Card stream[]={C3,S12,C13,S13,_Empty,D7,H6,S9,D9,D3,H4,D4,_Empty,S8,C7,D10,C8,C4,H12,C5,_Empty,H9,D8,C6,C2,H5,_Empty,C10,C9,S11,D11,D13,_Empty,H11,H10,H3,D5,H8,_Empty,C12,C11,H7,D6,_Empty,H13,D12,S10,H2,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(49,stream) ) );

}
void Step14(World& T)
{
	World Old=T;
	assert(T.DOWN(D9));
	int arr[]={6,1,5,4,6,6,1,0};
	assert( CheckNowMaxPos(T,arr,"14"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)!=T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(8)==D9);
	assert(T.P.FirstBlankLine()==(-1));
	assert(T.P.BlankLine().size()==0);
	
	//some HistoryItem verification
	assert(T.History.size()==14);
	assert(T.History[T.History.size()-1].Action==DOWN);
	assert(T.History[T.History.size()-1].Card1==D9);	
	

	//print NP and P
	PrintP(T);
	PrintNP(T);


	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

//size=48[C3,S12,C13,S13,_Empty,D7,H6,S9,C8,D3,H4,D4,D9,S8,C7,D10,C2,C4,H12,C5,_Empty,H9,D8,C6,D11,H5,_Empty,C10,C9,S11,D5,D13,_Empty,H11,H10,H3,D6,H8,_Empty,C12,C11,H7,H2,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={C3,S12,C13,S13,_Empty,D7,H6,S9,C8,D3,H4,D4,D9,S8,C7,D10,C2,C4,H12,C5,_Empty,H9,D8,C6,D11,H5,_Empty,C10,C9,S11,D5,D13,_Empty,H11,H10,H3,D6,H8,_Empty,C12,C11,H7,H2,_Empty,H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(48,stream) ) );

}

void Step15(World& T)
{
	World Old=T;
	assert(T.CONNECT(D9,C8));
	int arr[]={6,1,4,4,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"15"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)!=T.GetStrings(5));
	assert(Old.GetStrings(5)==T.GetStrings(4));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(8));
	assert(Old.GetStrings(8)!=T.GetStrings(7));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(8)==C8);
	assert(T.P.FirstBlankLine()==(-1));
	assert(T.P.BlankLine().size()==0);
	
	//some HistoryItem verification
	assert(T.History.size()==15);
	assert(T.History[T.History.size()-1].Action==CONNECT);
	assert(T.History[T.History.size()-1].Card1==D9);	
	assert(T.History[T.History.size()-1].Card2==C8);	

	//print NP and P
	PrintP(T);
	PrintNP(T);


	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);



//size=47[C3,S12,C13,S13,_Empty,D7,H6,S9,D3,C2,H4,C8,D4,S8,C7,D10,C4,D11,H12,D9,C5,H9,D8,C6,H5,D5,_Empty,C10,C9,S11,D13,D6,_Empty,H11,H10,H3,H8,H2,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={C3,S12,C13,S13,_Empty,D7,H6,S9,D3,C2,H4,C8,D4,S8,C7,D10,C4,D11,H12,D9,C5,H9,D8,C6,H5,D5,_Empty,C10,C9,S11,D13,D6,_Empty,H11,H10,H3,H8,H2,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(47,stream) ) );

}

void Step16(World& T)
{
	World Old=T;
	assert(T.FINISH(C2));
	int arr[]={6,1,3,4,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"16"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)!=T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(3)==D11);
	assert(T.P.FirstBlankLine()==(-1));
	assert(T.P.BlankLine().size()==0);
	
	//some HistoryItem verification
	assert(T.History.size()==16);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C2);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);


//size=46[C3,S12,C13,S13,_Empty,D7,H6,S9,D3,D11,H4,C8,D4,S8,C7,D10,C4,D5,H12,D9,C5,H9,D8,C6,H5,D6,_Empty,C10,C9,S11,D13,H2,_Empty,H11,H10,H3,H8,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={C3,S12,C13,S13,_Empty,D7,H6,S9,D3,D11,H4,C8,D4,S8,C7,D10,C4,D5,H12,D9,C5,H9,D8,C6,H5,D6,_Empty,C10,C9,S11,D13,H2,_Empty,H11,H10,H3,H8,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(46,stream) ) );

}

void Step17(World& T)
{
	World Old=T;
	assert(T.FINISH(C3));
	int arr[]={6,1,3,4,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"17"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()!=T.GetBufStrings());
	
	//some other verification
	assert(T.P.SearchBuffer(C3)==-1);
	assert(T.P.GetBufferSize()==3);
	
	//some HistoryItem verification
	assert(T.History.size()==17);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C3);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);



//size=45[S12,C13,S13,_Empty,D7,H6,S9,D3,D11,H4,C8,D4,S8,C7,D10,C4,D5,H12,D9,C5,H9,D8,C6,H5,D6,_Empty,C10,C9,S11,D13,H2,_Empty,H11,H10,H3,H8,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={S12,C13,S13,_Empty,D7,H6,S9,D3,D11,H4,C8,D4,S8,C7,D10,C4,D5,H12,D9,C5,H9,D8,C6,H5,D6,_Empty,C10,C9,S11,D13,H2,_Empty,H11,H10,H3,H8,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(45,stream) ) );

}

void Step18(World& T)
{
	World Old=T;
	assert(T.FINISH(D3));
	int arr[]={6,1,3,3,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"18"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)!=T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(4)==C4);
	assert(T.P.GetBufferSize()==3);
	
	//some HistoryItem verification
	assert(T.History.size()==18);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D3);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);


//size=44[S12,C13,S13,_Empty,D7,H6,S9,C4,D11,H4,C8,D4,S8,C7,D10,H5,D5,H12,D9,C5,H9,D8,C6,D13,D6,_Empty,C10,C9,S11,H8,H2,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={S12,C13,S13,_Empty,D7,H6,S9,C4,D11,H4,C8,D4,S8,C7,D10,H5,D5,H12,D9,C5,H9,D8,C6,D13,D6,_Empty,C10,C9,S11,H8,H2,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(44,stream) ) );

}

void Step19(World& T)
{
	World Old=T;
	assert(T.FINISH(D4));
	int arr[]={6,0,3,3,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"19"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(2)==C5);
	
	//some HistoryItem verification
	assert(T.History.size()==19);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D4);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

//size=44[S12,C13,S13,_Empty,D7,H6,S9,C4,D11,H4,C8,C5,S8,C7,D10,H5,D5,H12,D9,_Empty,H9,D8,C6,D13,D6,_Empty,C10,C9,S11,H8,H2,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={S12,C13,S13,_Empty,D7,H6,S9,C4,D11,H4,C8,C5,S8,C7,D10,H5,D5,H12,D9,_Empty,H9,D8,C6,D13,D6,_Empty,C10,C9,S11,H8,H2,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(44,stream) ) );

}


void Step20(World& T)
{
	World Old=T;
	assert(T.POP(D11));  
	int arr[]={6,0,2,3,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"20"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)!=T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()!=T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(3)==D5);
	assert(T.P.SearchBuffer(D11)==0);
	
	//some HistoryItem verification
	assert(T.History.size()==20);
	assert(T.History[T.History.size()-1].Action==POP);
	assert(T.History[T.History.size()-1].Card1==D11);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);



//size=44[D11,S12,C13,S13,_Empty,D7,H6,S9,C4,D5,H4,C8,C5,S8,C7,D10,H5,D6,H12,D9,_Empty,H9,D8,C6,D13,H2,_Empty,C10,C9,S11,H8,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,D7,H6,S9,C4,D5,H4,C8,C5,S8,C7,D10,H5,D6,H12,D9,_Empty,H9,D8,C6,D13,H2,_Empty,C10,C9,S11,H8,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(44,stream) ) );

}


void Step21(World& T)
{
	World Old=T;
	assert(T.FINISH(D5));  
	int arr[]={6,0,1,3,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"21"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)!=T.GetStrings(7));
	assert(Old.GetStrings(6)==T.GetStrings(5));
	assert(Old.GetStrings(7)==T.GetStrings(6));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(3)==D6);	
	
	//some HistoryItem verification
	assert(T.History.size()==21);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D5);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);


//size=43[D11,S12,C13,S13,_Empty,D7,H6,S9,C4,H4,C8,D6,C5,S8,C7,D10,H5,H12,D9,H2,_Empty,H9,D8,C6,D13,_Empty,C10,C9,S11,H8,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,D7,H6,S9,C4,H4,C8,D6,C5,S8,C7,D10,H5,H12,D9,H2,_Empty,H9,D8,C6,D13,_Empty,C10,C9,S11,H8,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(43,stream) ) );

}

void Step22(World& T)
{
	World Old=T;
	assert(T.FINISH(D6));  
	int arr[]={6,0,0,3,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"22"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)!=T.GetStrings(8));
	assert(Old.GetStrings(8)==T.GetStrings(7));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(3)==H2);	
	
	//some HistoryItem verification
	assert(T.History.size()==22);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D6);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

//size=42[D11,S12,C13,S13,_Empty,D7,H6,S9,C4,H4,C8,C5,H2,S8,C7,D10,H5,H12,D9,_Empty,H9,D8,C6,D13,_Empty,C10,C9,S11,H8,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
		D7,H6,S9,C4,H4,C8,C5,H2,S8,C7,D10,H5,H12,D9,_Empty,
		H9,D8,C6,D13,_Empty,
		C10,C9,S11,H8,_Empty,
		H11,H10,H3,_Empty,
		C12,C11,H7,_Empty,
		H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(42,stream) ) );

}


void Step23(World& T)
{
	World Old=T;
	assert(T.FINISH(H2));  
	int arr[]={6,0,-1,3,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"23"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(3)==_Empty);	
	
	//some HistoryItem verification
	assert(T.History.size()==23);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H2);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);
//size=42[D11,S12,C13,S13,_Empty,D7,H6,S9,C4,H4,C8,C5,_Empty,S8,C7,D10,H5,H12,D9,_Empty,H9,D8,C6,D13,_Empty,C10,C9,S11,H8,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]
	Card stream[]={D11,S12,C13,S13,_Empty,
		D7,H6,S9,C4,H4,C8,C5,_Empty,
		S8,C7,D10,H5,H12,D9,_Empty,
		H9,D8,C6,D13,_Empty,
		C10,C9,S11,H8,_Empty,
		H11,H10,H3,_Empty,
		C12,C11,H7,_Empty,
		H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(42,stream) ) );

}


void Step24(World& T)
{
	World Old=T;
	assert(T.FINISH(C4));  
	int arr[]={6,0,-1,2,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"24"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)!=T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(4)==H5);	
	
	//some HistoryItem verification
	assert(T.History.size()==24);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C4);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

//size=41[D11,S12,C13,S13,_Empty,D7,H6,S9,H5,H4,C8,C5,_Empty,S8,C7,D10,D13,H12,D9,_Empty,H9,D8,C6,H8,_Empty,C10,C9,S11,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
		D7,H6,S9,H5,H4,C8,C5,_Empty,
		S8,C7,D10,D13,H12,D9,_Empty,
		H9,D8,C6,H8,_Empty,
		C10,C9,S11,_Empty,
		H11,H10,H3,_Empty,
		C12,C11,H7,_Empty,
		H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(41,stream) ) );

}

void Step25(World& T)
{
	World Old=T;
	assert(T.FINISH(C5));  
	int arr[]={6,-1,-1,2,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"25"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)!=T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(2)==_Empty);	
	assert(T.P.BlankLine().size()==2);
	assert(T.P.FirstBlankLine()==2);
	
	//some HistoryItem verification
	assert(T.History.size()==25);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C5);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

//size=40[D11,S12,C13,S13,_Empty,D7,H6,S9,H5,H4,C8,_Empty,S8,C7,D10,D13,H12,D9,_Empty,H9,D8,C6,H8,_Empty,C10,C9,S11,_Empty,H11,H10,H3,_Empty,C12,C11,H7,_Empty,H13,D12,S10,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
		D7,H6,S9,H5,H4,C8,_Empty,
		S8,C7,D10,D13,H12,D9,_Empty,
		H9,D8,C6,H8,_Empty,
		C10,C9,S11,_Empty,
		H11,H10,H3,_Empty,
		C12,C11,H7,_Empty,
		H13,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(40,stream) ) );

}


void Step26(World& T)
{
	World Old=T;
	assert(T.FINISH(D7));  
	int arr[]={5,-1,-1,2,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"26"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)!=T.GetStrings(3));
	assert(Old.GetStrings(2)==T.GetStrings(1));
	assert(Old.GetStrings(3)==T.GetStrings(2));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(1)==S8);	

	//some HistoryItem verification
	assert(T.History.size()==26);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D7);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);


//size=39[D11,S12,C13,S13,_Empty,H6,S9,S8,H5,H4,C8,_Empty,C7,D10,H9,D13,H12,D9,_Empty,D8,C6,C10,H8,_Empty,C9,S11,H11,_Empty,H10,H3,C12,_Empty,C11,H7,H13,_Empty,D12,S10,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
		H6,S9,S8,H5,H4,C8,_Empty,
		C7,D10,H9,D13,H12,D9,_Empty,
		D8,C6,C10,H8,_Empty,
		C9,S11,H11,_Empty,
		H10,H3,C12,_Empty,
		C11,H7,H13,_Empty,
		D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(39,stream) ) );

}

void Step27(World& T)
{
	World Old=T;
	assert(T.FINISH(S8));  
	int arr[]={4,-1,-1,2,6,6,1,1};
	assert( CheckNowMaxPos(T,arr,"27"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)!=T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(1)==H9);	

	//some HistoryItem verification
	assert(T.History.size()==27);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S8);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

//size=38[D11,S12,C13,S13,_Empty,H6,S9,H9,H5,H4,C8,_Empty,C7,D10,C10,D13,H12,D9,_Empty,D8,C6,H11,H8,_Empty,C9,S11,C12,_Empty,H10,H3,H13,_Empty,C11,H7,_Empty,D12,S10,_EndOfStream]
	Card stream[]={D11,S12,C13,S13,_Empty,H6,S9,H9,H5,H4,C8,_Empty,C7,D10,C10,D13,H12,D9,_Empty,D8,C6,H11,H8,_Empty,C9,S11,C12,_Empty,H10,H3,H13,_Empty,C11,H7,_Empty,D12,S10,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(38,stream) ) );

}

void Step28(World& T)
{
	World Old=T;
	assert(T.FINISH(S9));  
	int arr[]={4,-1,-1,2,5,6,1,1};
	assert( CheckNowMaxPos(T,arr,"28"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)!=T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(5)==D10);	

	//some HistoryItem verification
	assert(T.History.size()==28);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S9);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);


//size=37[D11,S12,C13,S13,_Empty,H6,D10,H9,H5,H4,C8,_Empty,C7,C6,C10,D13,H12,D9,_Empty,D8,S11,H11,H8,_Empty,C9,H3,C12,_Empty,H10,H7,H13,_Empty,C11,S10,_Empty,D12,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,H6,D10,H9,H5,H4,C8,_Empty,C7,C6,C10,D13,H12,D9,_Empty,D8,S11,H11,H8,_Empty,C9,H3,C12,_Empty,H10,H7,H13,_Empty,C11,S10,_Empty,D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(37,stream) ) );


}


void Step29(World& T)
{
	World Old=T;
	assert(T.DOWN(D10));  
	int arr[]={4,0,-1,2,4,6,1,1};
	assert( CheckNowMaxPos(T,arr,"29"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)!=T.GetStrings(3));
	assert(Old.GetStrings(3)==T.GetStrings(2));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)!=T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(2)==D10);	
	assert(T.P.Peek(5)==C6);
	//some HistoryItem verification
	assert(T.History.size()==29);
	assert(T.History[T.History.size()-1].Action==DOWN);
	assert(T.History[T.History.size()-1].Card1==D10);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);



//size=37[D11,S12,C13,S13,_Empty,H6,H9,C6,H5,H4,C8,D10,_Empty,C7,C10,S11,D13,H12,D9,_Empty,D8,H11,H3,H8,_Empty,C9,C12,H7,_Empty,H10,H13,S10,_Empty,C11,_Empty,D12,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,H6,H9,C6,H5,H4,C8,D10,_Empty,C7,C10,S11,D13,H12,D9,_Empty,D8,H11,H3,H8,_Empty,C9,C12,H7,_Empty,H10,H13,S10,_Empty,C11,_Empty,D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(37,stream) ) );

}


void Step30(World& T)
{
	World Old=T;
	assert(T.FINISH(C6));  
	int arr[]={4,0,-1,2,3,6,1,1};
	assert( CheckNowMaxPos(T,arr,"30"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)!=T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(5)==S11);	
	//some HistoryItem verification
	assert(T.History.size()==30);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C6);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);


//[D11,S12,C13,S13,_Empty,H6,H9,S11,H5,H4,C8,D10,_Empty,C7,C10,H3,D13,H12,D9,_Empty,D8,H11,H7,H8,_Empty,C9,C12,S10,_Empty,H10,H13,_Empty,C11,_Empty,D12,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
		H6,H9,S11,H5,H4,C8,D10,_Empty,
		C7,C10,H3,D13,H12,D9,_Empty,
		D8,H11,H7,H8,_Empty,
		C9,C12,S10,_Empty,
		H10,H13,_Empty,
		C11,_Empty,
		D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(36,stream) ) );


}


void Step31(World& T)
{
	World Old=T;
	assert(T.DOWN(S11));  
	int arr[]={4,0,0,2,2,6,1,1};
	assert( CheckNowMaxPos(T,arr,"31"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)!=T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(8));
	assert(Old.GetStrings(8)!=T.GetStrings(7));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(3)==S11);	
	assert(T.P.Peek(5)==H3);
	//some HistoryItem verification
	assert(T.History.size()==31);
	assert(T.History[T.History.size()-1].Action==DOWN);
	assert(T.History[T.History.size()-1].Card1==S11);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);


//[D11,S12,C13,S13,_Empty,H6,H9,H3,H5,H4,C8,S11,D10,C7,C10,H7,D13,H12,D9,_Empty,D8,H11,S10,H8,_Empty,C9,C12,_Empty,H10,H13,_Empty,C11,_Empty,D12,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
		H6,H9,H3,H5,H4,C8,S11,D10,C7,C10,H7,D13,H12,D9,_Empty,
		D8,H11,S10,H8,_Empty,
		C9,C12,_Empty,
		H10,H13,_Empty,
		C11,_Empty,
		D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(35,stream) ) );

}


void Step32(World& T)
{
	World Old=T;
	assert(T.FINISH(H3));  
	int arr[]={4,0,0,2,1,6,1,1};
	assert( CheckNowMaxPos(T,arr,"32"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)!=T.GetStrings(5));
	assert(Old.GetStrings(4)==T.GetStrings(3));
	assert(Old.GetStrings(5)==T.GetStrings(4));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(5)==H7);
	//some HistoryItem verification
	assert(T.History.size()==32);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H3);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);

//size=34
//[D11,S12,C13,S13,_Empty,H6,H9,H5,H4,H7,C8,S11,D10,C7,C10,D13,H12,S10,D9,_Empty,D8,H11,H8,_Empty,C9,C12,_Empty,H10,H13,_Empty,C11,_Empty,D12,_EndOfStream]


	Card stream[]={D11,S12,C13,S13,_Empty,
		H6,H9,H5,H4,H7,C8,S11,D10,C7,C10,D13,H12,S10,D9,_Empty,
		D8,H11,H8,_Empty,
		C9,C12,_Empty,
		H10,H13,_Empty,
		C11,_Empty,
		D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(34,stream) ) );


}

void Step33(World& T)
{
	World Old=T;
	assert(T.FINISH(H4));  
	int arr[]={4,0,0,2,1,6,0,1};
	assert( CheckNowMaxPos(T,arr,"33"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)!=T.GetStrings(6));
	assert(Old.GetStrings(5)==T.GetStrings(4));
	assert(Old.GetStrings(6)==T.GetStrings(5));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	

	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(7)==H12);
	//some HistoryItem verification
	assert(T.History.size()==33);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H4);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector(); cout<<"size="<< hand.size();
	that.PrintVector(hand);
	

//[D11,S12,C13,S13,_Empty,H6,H9,H5,H7,C8,H12,S11,D10,C7,C10,D13,S10,D9,_Empty,D8,H11,H8,_Empty,C9,C12,_Empty,H10,H13,_Empty,C11,_Empty,D12,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
					H6,H9,H5,H7,C8,H12,S11,D10,
					C7,C10,D13,S10,D9,_Empty,
					D8,H11,H8,_Empty,
					C9,C12,_Empty,
					H10,H13,_Empty,
					C11,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(33,stream) ) );

}


void Step34(World& T)
{
	World Old=T;
	assert(T.FINISH(H5));  
	int arr[]={4,0,0,1,1,6,0,1};
	assert( CheckNowMaxPos(T,arr,"34"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	
	assert(Old.GetStrings(3)!=T.GetStrings(5));
	assert(Old.GetStrings(4)==T.GetStrings(3));
	assert(Old.GetStrings(5)==T.GetStrings(4));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));

	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(4)==D13);
	//some HistoryItem verification
	assert(T.History.size()==34);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H5);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);

//[D11,S12,C13,S13,_Empty,H6,H9,H7,C8,D13,H12,S11,D10,C7,C10,S10,D9,H8,_Empty,D8,H11,_Empty,C9,C12,_Empty,H10,H13,_Empty,C11,_Empty,D12,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
					H6,H9,H7,C8,D13,H12,S11,D10,
					C7,C10,S10,D9,H8,_Empty,
					D8,H11,_Empty,
					C9,C12,_Empty,
					H10,H13,_Empty,
					C11,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(32,stream) ) );


}

void Step35(World& T)
{
	World Old=T;
	assert(T.FINISH(H6));  
	int arr[]={4,0,0,1,1,5,0,1};
	assert( CheckNowMaxPos(T,arr,"35"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)!=T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));

	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(6)==C7);
	//some HistoryItem verification
	assert(T.History.size()==35);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H6);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);



//[D11,S12,C13,S13,_Empty,C7,H9,H7,C8,D13,H12,S11,D10,D8,C10,S10,D9,H8,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,H13,_Empty,D12,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
					C7,H9,H7,C8,D13,H12,S11,D10,D8,C10,S10,D9,H8,_Empty,
					C9,H11,_Empty,
					H10,C12,_Empty,
					C11,H13,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(30,stream) ) );

}

void Step36(World& T)
{
	World Old=T;
	assert(T.FINISH(H7));  
	int arr[]={4,0,0,1,0,5,0,1};
	assert( CheckNowMaxPos(T,arr,"36"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	
	assert(Old.GetStrings(3)!=T.GetStrings(7));
	assert(Old.GetStrings(4)==T.GetStrings(3));
	assert(Old.GetStrings(5)==T.GetStrings(4));
	assert(Old.GetStrings(6)==T.GetStrings(5));
	assert(Old.GetStrings(7)==T.GetStrings(6));
	assert(Old.GetStrings(8)==T.GetStrings(8));

	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(5)==S10);
	//some HistoryItem verification
	assert(T.History.size()==36);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H7);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);


//[D11,S12,C13,S13,_Empty,C7,H9,C8,D13,H12,S11,S10,D10,D8,C10,D9,H8,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,H13,_Empty,D12,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
					C7,H9,C8,D13,H12,S11,S10,D10,D8,C10,D9,H8,_Empty,
					C9,H11,_Empty,
					H10,C12,_Empty,
					C11,H13,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(29,stream) ) );

}




void Step37(World& T)
{
	World Old=T;
	assert(T.FINISH(S10));  
	int arr[]={4,0,0,1,-1,5,0,1};
	assert( CheckNowMaxPos(T,arr,"37"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));
	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)!=T.GetStrings(8));
	assert(Old.GetStrings(8)==T.GetStrings(7));

	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(5)==_Empty);
	//some HistoryItem verification
	assert(T.History.size()==37);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S10);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);


//[D11,S12,C13,S13,_Empty,C7,H9,C8,D13,H12,S11,D10,_Empty,D8,C10,D9,H8,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,H13,_Empty,D12,_EndOfStream]

	Card stream[]={D11,S12,C13,S13,_Empty,
				   C7,H9,C8,D13,H12,S11,D10,_Empty,
				   D8,C10,D9,H8,_Empty,
				   C9,H11,_Empty,
				   H10,C12,_Empty,
				   C11,H13,_Empty,
				   D12,_EndOfStream };

	assert ( checkGetBytes(T, ArrCardToVecCard(29,stream) ) );

}


void Step38(World& T)
{
	World Old=T;
	assert(T.DOWN(D13));  
	int arr[]={4,0,0,0,0,5,0,1};
	assert( CheckNowMaxPos(T,arr,"38"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	
	assert(Old.GetStrings(4)!=T.GetStrings(8));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(5)==D13);
	assert(T.P.Peek(4)==H8);
	//some HistoryItem verification
	assert(T.History.size()==38);
	assert(T.History[T.History.size()-1].Action==DOWN);
	assert(T.History[T.History.size()-1].Card1==D13);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);


//[D11,S12,C13,S13,_Empty,C7,H9,C8,D13,H12,S11,D10,H8,D8,C10,D9,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,H13,_Empty,D12,_EndOfStream]


	Card stream[]={ D11,S12,C13,S13,_Empty,
					C7,H9,C8,D13,H12,S11,D10,H8,D8,C10,D9,_Empty,
					C9,H11,_Empty,
					H10,C12,_Empty,
					C11,H13,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(28,stream) ) );

}


void Step39(World& T)
{
	World Old=T;
	assert(T.FINISH(H8));  
	int arr[]={4,0,0,-1,0,5,0,1};
	assert( CheckNowMaxPos(T,arr,"39"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)!=T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(4)==_Empty);
	//some HistoryItem verification
	assert(T.History.size()==39);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H8);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);




//[D11,S12,C13,S13,_Empty,C7,H9,C8,D13,H12,S11,D10,_Empty,D8,C10,D9,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,H13,_Empty,D12,_EndOfStream]

	Card stream[]={ D11,S12,C13,S13,_Empty,
					C7,H9,C8,D13,H12,S11,D10,_Empty,
					D8,C10,D9,_Empty,
					C9,H11,_Empty,
					H10,C12,_Empty,
					C11,H13,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(28,stream) ) );

}


void Step40(World& T)
{
	World Old=T;
	assert(T.FINISH(S11));  
	int arr[]={4,0,-1,-1,0,5,0,1};
	assert( CheckNowMaxPos(T,arr,"40"));
	PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));

	assert(Old.GetStrings(6)!=T.GetStrings(8));
	assert(Old.GetStrings(7)==T.GetStrings(6));
	assert(Old.GetStrings(8)==T.GetStrings(7));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.Peek(3)==_Empty);
	//some HistoryItem verification
	assert(T.History.size()==40);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S11);	

	//print NP and P
	PrintP(T);
	PrintNP(T);


	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);




//[D11,S12,C13,S13,_Empty,C7,H9,C8,D13,H12,D10,_Empty,D8,C10,D9,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,H13,_Empty,D12,_EndOfStream]
	Card stream[]={ D11,S12,C13,S13,_Empty,
					C7,H9,C8,D13,H12,D10,_Empty,
					D8,C10,D9,_Empty,
					C9,H11,_Empty,
					H10,C12,_Empty,
					C11,H13,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(27,stream) ) );


}


void Step41(World& T)
{
	World Old=T;
	assert(T.FINISH(S12));  
	int arr[]={4,0,-1,-1,0,5,0,1};
	assert( CheckNowMaxPos(T,arr,"41"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()!=T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==3);
	//some HistoryItem verification
	assert(T.History.size()==41);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S12);	

	//print NP and P
	PrintP(T);
	PrintNP(T);


	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);

//[D11,C13,S13,_Empty,C7,H9,C8,D13,H12,D10,_Empty,D8,C10,D9,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,H13,_Empty,D12,_EndOfStream]



	Card stream[]={ D11,C13,S13,_Empty,
					C7,H9,C8,D13,H12,D10,_Empty,
					D8,C10,D9,_Empty,
					C9,H11,_Empty,
					H10,C12,_Empty,
					C11,H13,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(26,stream) ) );


}


void Step42(World& T)
{
	World Old=T;
	assert(T.FINISH(S13));  
	int arr[]={4,0,-1,-1,0,5,0,1};
	assert( CheckNowMaxPos(T,arr,"42"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()!=T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==2);
	//some HistoryItem verification
	assert(T.History.size()==42);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==S13);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);

//[D11,C13,_Empty,C7,H9,C8,D13,H12,D10,_Empty,D8,C10,D9,_Empty,C9,H11,_Empty,H10,C12,_Empty,C11,H13,_Empty,D12,_EndOfStream]


	Card stream[]={ D11,C13,_Empty,
					C7,H9,C8,D13,H12,D10,_Empty,
					D8,C10,D9,_Empty,
					C9,H11,_Empty,
					H10,C12,_Empty,
					C11,H13,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(25,stream) ) );

}


void Step43(World& T)
{
	World Old=T;
	assert(T.FINISH(H9));  
	int arr[]={3,0,-1,-1,0,5,0,1};
	assert( CheckNowMaxPos(T,arr,"43"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)!=T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==2);
	//some HistoryItem verification
	assert(T.History.size()==43);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H9);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);

//[D11,C13,_Empty,C7,C10,C8,D13,H12,D10,_Empty,D8,H11,D9,_Empty,C9,C12,_Empty,H10,H13,_Empty,C11,_Empty,D12,_EndOfStream]

	Card stream[]={ D11,C13,_Empty,
					C7,C10,C8,D13,H12,D10,_Empty,
					D8,H11,D9,_Empty,
					C9,C12,_Empty,
					H10,H13,_Empty,
					C11,_Empty,
					D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(24,stream) ) );

}

void Step44(World& T)
{
	World Old=T;
	assert(T.FINISH(C7));  
	int arr[]={3,0,-1,-1,0,4,0,1};
	assert( CheckNowMaxPos(T,arr,"44"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)!=T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==2);
	//some HistoryItem verification
	assert(T.History.size()==44);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C7);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);

//[D11,C13,_Empty,D8,C10,C8,D13,H12,D10,_Empty,C9,H11,D9,_Empty,H10,C12,_Empty,C11,H13,_Empty,D12,_EndOfStream]


	Card stream[]={ D11,C13,_Empty,
					D8,C10,C8,D13,H12,D10,_Empty,
					C9,H11,D9,_Empty,
					H10,C12,_Empty,
					C11,H13,_Empty,D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(22,stream) ) );

}
	
void Step45(World& T)
{
	World Old=T;
	assert(T.FINISH(D8));  
	int arr[]={3,0,-1,-1,0,3,0,1};
	assert( CheckNowMaxPos(T,arr,"45"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)!=T.GetStrings(2));
	assert(Old.GetStrings(2)==T.GetStrings(1));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==2);
	//some HistoryItem verification
	assert(T.History.size()==45);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D8);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);



//[D11,C13,_Empty,C10,C9,C8,D13,H12,D10,_Empty,H11,H10,D9,_Empty,C12,C11,_Empty,H13,D12,_EndOfStream]


	Card stream[]={D11,C13,_Empty,
					C10,C9,C8,D13,H12,D10,_Empty,
					H11,H10,D9,_Empty,C12,C11,_Empty,H13,D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(20,stream) ) );
}
	
	
void Step46(World& T)
{
	World Old=T;
	assert(T.FINISH(C8));  
	int arr[]={3,0,-1,-1,0,3,0,0};
	assert( CheckNowMaxPos(T,arr,"46"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)!=T.GetStrings(6));
	assert(Old.GetStrings(4)==T.GetStrings(3));
	assert(Old.GetStrings(5)==T.GetStrings(4));
	assert(Old.GetStrings(6)==T.GetStrings(5));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==2);
	//some HistoryItem verification
	assert(T.History.size()==46);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C8);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);


//[D11,C13,_Empty,C10,C9,D13,H12,D10,D9,_Empty,H11,H10,_Empty,C12,C11,_Empty,H13,D12,_EndOfStream]

	Card stream[]={D11,C13,_Empty,
				   C10,C9,D13,H12,D10,D9,_Empty,
				   H11,H10,_Empty,
				   C12,C11,_Empty,
				   H13,D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(19,stream) ) );
}
	
	
void Step47(World& T)
{
	World Old=T;
	assert(T.FINISH(D9));  
	int arr[]={3,0,-1,-1,0,3,0,-1};
	assert( CheckNowMaxPos(T,arr,"47"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)!=T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==2);
	assert(T.P.BlankLine().size()==3);

	//some HistoryItem verification
	assert(T.History.size()==47);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D9);	

	//print NP and P
	PrintP(T);
	PrintNP(T);


	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);

//[D11,C13,_Empty,C10,C9,D13,H12,D10,_Empty,H11,H10,_Empty,C12,C11,_Empty,H13,D12,_EndOfStream]

	Card stream[]={ D11,C13,_Empty,
					C10,C9,D13,H12,D10,_Empty,
					H11,H10,_Empty,
					C12,C11,_Empty,
					H13,D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(18,stream) ) );


}
	
	
void Step48(World& T)
{
	World Old=T;
	assert(T.FINISH(D10));  
	int arr[]={3,-1,-1,-1,0,3,0,-1};
	assert( CheckNowMaxPos(T,arr,"48"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)!=T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==2);
	assert(T.P.BlankLine().size()==4);

	//some HistoryItem verification
	assert(T.History.size()==48);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D10);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);

//[D11,C13,_Empty,C10,C9,D13,H12,_Empty,H11,H10,_Empty,C12,C11,_Empty,H13,D12,_EndOfStream]

	Card stream[]={ D11,C13,_Empty,
					C10,C9,D13,H12,_Empty,
					H11,H10,_Empty,
					C12,C11,_Empty,
					H13,D12,_EndOfStream };

	assert ( checkGetBytes(T, ArrCardToVecCard(17,stream) ) );


}
	
void Step49(World& T)
{
	World Old=T;
	assert(T.FINISH(D11));  
	int arr[]={3,-1,-1,-1,0,3,0,-1};
	assert( CheckNowMaxPos(T,arr,"49"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()!=T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==4);

	//some HistoryItem verification
	assert(T.History.size()==49);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D11);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	//[C13,_Empty,C10,C9,D13,H12,_Empty,H11,H10,_Empty,C12,C11,_Empty,H13,D12,_EndOfStream]
	Card stream[]={ C13,_Empty,
					C10,C9,D13,H12,_Empty,
					H11,H10,_Empty,
					C12,C11,_Empty,
					H13,D12,_EndOfStream};

	assert ( checkGetBytes(T, ArrCardToVecCard(16,stream) ) );

}
	
	
void Step50(World& T)
{
	World Old=T;
	assert(T.FINISH(C9));  
	int arr[]={3,-1,-1,-1,0,2,0,-1};
	assert( CheckNowMaxPos(T,arr,"50"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)!=T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==4);

	//some HistoryItem verification
	assert(T.History.size()==50);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C9);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13,_Empty,
					C10,H10,D13,H12,_Empty,
					H11,C11,_Empty,
					C12,D12,_Empty,
					H13,_EndOfStream};


	assert ( checkGetBytes(T, ArrCardToVecCard(15,stream) ) );


}
	
void Step51(World& T)
{
	World Old=T;
	assert(T.FINISH(H10));  
	int arr[]={3,-1,-1,-1,0,1,0,-1};
	assert( CheckNowMaxPos(T,arr,"51"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)!=T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==4);

	//some HistoryItem verification
	assert(T.History.size()==51);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H10);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13,_Empty,
					C10,C11,D13,H12,_Empty,
					H11,D12,_Empty,
					C12,_Empty,
					H13,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(14,stream) ) );


}

	
void Step52(World& T)
{
	World Old=T;
	assert(T.FINISH(C10));  
	int arr[]={2,-1,-1,-1,0,1,0,-1};
	assert( CheckNowMaxPos(T,arr,"52"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)!=T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==4);

	//some HistoryItem verification
	assert(T.History.size()==52);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C10);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13,_Empty,
					H11,C11,D13,H12,_Empty,
					C12,D12,_Empty,
					H13,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(12,stream) ) );

}
	
void Step53(World& T)
{
	World Old=T;
	assert(T.FINISH(H11));  
	int arr[]={1,-1,-1,-1,0,1,0,-1};
	assert( CheckNowMaxPos(T,arr,"53"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)!=T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==4);

	//some HistoryItem verification
	assert(T.History.size()==53);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H11);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13,_Empty,
					C12,C11,D13,H12,_Empty,
					H13,D12,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(10,stream) ) );


}
	
void Step54(World& T)
{
	World Old=T;
	assert(T.FINISH(H12));  
	int arr[]={1,-1,-1,-1,0,1,-1,-1};
	assert( CheckNowMaxPos(T,arr,"54"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)!=T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==5);

	//some HistoryItem verification
	assert(T.History.size()==54);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H12);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13,_Empty,
					C12,C11,D13,_Empty,
					H13,D12,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(9,stream) ) );


}

void Step55(World& T)
{
	World Old=T;
	assert(T.FINISH(C11));  
	int arr[]={1,-1,-1,-1,0,0,-1,-1};
	assert( CheckNowMaxPos(T,arr,"55"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)!=T.GetStrings(3));	
	assert(Old.GetStrings(3)==T.GetStrings(2));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==5);

	//some HistoryItem verification
	assert(T.History.size()==55);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C11);	

	//print NP and P
	PrintP(T);
	PrintNP(T);


	//這一段要印getBytes()應該有的值
	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13,_Empty,
					C12,D13,D12,_Empty,
					H13,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(8,stream) ) );

}

void Step56(World& T)
{
	World Old=T;
	assert(T.FINISH(D12));  
	int arr[]={1,-1,-1,-1,0,-1,-1,-1};
	assert( CheckNowMaxPos(T,arr,"56"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)!=T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==6);

	//some HistoryItem verification
	assert(T.History.size()==56);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D12);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	//這一段要印getBytes()應該有的值
	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13,_Empty,
					C12,D13,_Empty,
					H13,_EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(7,stream) ) );

}


void Step57(World& T)
{
	World Old=T;
	assert(T.FINISH(D13));  
	int arr[]={1,-1,-1,-1,-1,-1,-1,-1};
	assert( CheckNowMaxPos(T,arr,"57"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)!=T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==7);

	//some HistoryItem verification
	assert(T.History.size()==57);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==D13);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	//這一段要印getBytes()應該有的值
	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13,_Empty,
					C12,_Empty, H13, _EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(6,stream) ) );


}


void Step58(World& T)
{
	World Old=T;
	assert(T.FINISH(C12));  
	int arr[]={0,-1,-1,-1,-1,-1,-1,-1};
	assert( CheckNowMaxPos(T,arr,"58"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)!=T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==7);

	//some HistoryItem verification
	assert(T.History.size()==58);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C12);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	//這一段要印getBytes()應該有的值
	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13,_Empty,H13, _EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(4,stream) ) );


}




void Step59(World& T)
{
	World Old=T;
	assert(T.FINISH(H13));  
	int arr[]={-1,-1,-1,-1,-1,-1,-1,-1};
	assert( CheckNowMaxPos(T,arr,"59"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)!=T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()==T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==1);
	assert(T.P.BlankLine().size()==8);

	//some HistoryItem verification
	assert(T.History.size()==59);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==H13);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	//這一段要印getBytes()應該有的值
	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ C13, _EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(2,stream) ) );

}

void Step60(World& T)
{
	World Old=T;
	assert(T.FINISH(C13));  
	int arr[]={-1,-1,-1,-1,-1,-1,-1,-1};
	assert( CheckNowMaxPos(T,arr,"60"));
	//PrintNP(T);
	
	assert(Old.GetStrings(1)==T.GetStrings(1));
	assert(Old.GetStrings(2)==T.GetStrings(2));	
	assert(Old.GetStrings(3)==T.GetStrings(3));
	assert(Old.GetStrings(4)==T.GetStrings(4));
	assert(Old.GetStrings(5)==T.GetStrings(5));
	assert(Old.GetStrings(6)==T.GetStrings(6));
	assert(Old.GetStrings(7)==T.GetStrings(7));
	assert(Old.GetStrings(8)==T.GetStrings(8));
	assert(Old.GetBufStrings()!=T.GetBufStrings());
	
	//some other verification
	assert(T.P.GetBufferSize()==0);
	assert(T.P.BlankLine().size()==8);
	assert(T.isComplete()==true);

	//some HistoryItem verification
	assert(T.History.size()==60);
	assert(T.History[T.History.size()-1].Action==FINISH);
	assert(T.History[T.History.size()-1].Card1==C13);	

	//print NP and P
	PrintP(T);
	PrintNP(T);

	//這一段要印getBytes()應該有的值
	NP that(T.P);
	vector<Card> hand=that.getVector();
	that.PrintVector(hand);
	
	Card stream[]={ _EndOfStream};
	assert ( checkGetBytes(T, ArrCardToVecCard(1,stream) ) );

}


