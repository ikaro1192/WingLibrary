#include "../gtest/gtest.h"
#include "../wing/seen_transition/seen_transition.hpp"
#include <iostream>


class SeenTransitionTestClass1{
public:
	typedef int Parameter;

	SeenTransitionTestClass1(bool& FocusOnFlag_,int& FocusOnParameter_,bool& CallFlag_):
		FocusOnFlag(FocusOnFlag_),
		FocusOnParameter(FocusOnParameter_),
		CallFlag(CallFlag_)
	{}

	template<class T>
	void run(T& Manager){
		CallFlag=true;
	}

	void focusOn(){FocusOnFlag=true;}
	void focusOn(int a){FocusOnFlag=true;FocusOnParameter=a;}


	void focusOut(){
		FocusOnFlag=false;
		CallFlag=false;
	}

private:
	bool& FocusOnFlag;
	int& FocusOnParameter;
	bool& CallFlag;
};

class SeenTransitionTestClass2{
public:
	typedef int Parameter;
	SeenTransitionTestClass2(bool& FocusOnFlag_,int& FocusOnParameter_,bool& CallFlag_):
		FocusOnFlag(FocusOnFlag_),
		FocusOnParameter(FocusOnParameter_),
		CallFlag(CallFlag_)
		{}

	template<class T>
	void run(T& Manager){
		CallFlag=true;
	}

	void focusOn(){FocusOnFlag=true;}
	void focusOn(int a){FocusOnFlag=true;FocusOnParameter=a;}


	void focusOut(){
		FocusOnFlag=false;
		CallFlag=false;
	}

private:
	bool& FocusOnFlag;
	int& FocusOnParameter;
	bool& CallFlag;
};


//èâä˙âªÉeÉXÉg
TEST( Seen_Transition_Test, InitializeTest ){

	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;

	auto Manager=wing::seen_transition::
		SeenManager<SeenTransitionTestClass1,SeenTransitionTestClass2>
		(SeenTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1),SeenTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2));
	
	EXPECT_EQ(0,Manager.getNowTarget()); 

}

TEST( Seen_Transition_Test, ChangeFocusTestNonParameter ){
 
	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;
	auto Manager=wing::seen_transition::SeenManager<SeenTransitionTestClass1,SeenTransitionTestClass2>(SeenTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1),SeenTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2));
	

	Manager.changeFocus<SeenTransitionTestClass1>();
	EXPECT_EQ(0,Manager.getNowTarget()); 
	EXPECT_EQ(true,FocusOnFlag1); 
	EXPECT_EQ(false,FocusOnFlag2); 


	Manager.changeFocus<SeenTransitionTestClass2>();
	EXPECT_EQ(1,Manager.getNowTarget()); 
	EXPECT_EQ(false,FocusOnFlag1); 
	EXPECT_EQ(true,FocusOnFlag2); 


	Manager.changeFocus<SeenTransitionTestClass1>();
	EXPECT_EQ(0,Manager.getNowTarget()); 
	EXPECT_EQ(true,FocusOnFlag1); 
	EXPECT_EQ(false,FocusOnFlag2); 



}

TEST( Seen_Transition_Test, ChangeFocusTestParameter ){
 
	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;
	auto Manager=wing::seen_transition::SeenManager<SeenTransitionTestClass1,SeenTransitionTestClass2>(SeenTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1),SeenTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2));
	


	Manager.changeFocus<SeenTransitionTestClass1>(10);
	EXPECT_EQ(0,Manager.getNowTarget()); 
	EXPECT_EQ(true,FocusOnFlag1); 
	EXPECT_EQ(false,FocusOnFlag2); 
	EXPECT_EQ(10,FocusOnParameter1); 

	
	Manager.changeFocus<SeenTransitionTestClass2>(4);
	EXPECT_EQ(1,Manager.getNowTarget()); 
	EXPECT_EQ(false,FocusOnFlag1); 
	EXPECT_EQ(true,FocusOnFlag2); 
	EXPECT_EQ(4,FocusOnParameter2);

	
	Manager.changeFocus<SeenTransitionTestClass1>(2);
	EXPECT_EQ(0,Manager.getNowTarget()); 
	EXPECT_EQ(true,FocusOnFlag1); 
	EXPECT_EQ(false,FocusOnFlag2); 
	EXPECT_EQ(2,FocusOnParameter1);
	

}


TEST( Seen_Transition_Test, RunTest ){
	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;
	auto Manager=wing::seen_transition::SeenManager<SeenTransitionTestClass1,SeenTransitionTestClass2>(SeenTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1),SeenTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2));
	
	Manager.run();
	EXPECT_EQ(true,CallFlag1);
	EXPECT_EQ(false,CallFlag2); 

	Manager.changeFocus<SeenTransitionTestClass2>();
	Manager.run();
	EXPECT_EQ(false,CallFlag1);
	EXPECT_EQ(true,CallFlag2); 


}
