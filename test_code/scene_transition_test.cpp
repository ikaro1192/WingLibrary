#include "../gtest/gtest.h"
#include "../wing/scene_transition/scene_transition.hpp"
#include <iostream>
#pragma warning( disable : 4512 )


class MyEvent{
public:
};

class SceneTransitionTestClass1{
public:
	typedef int Parameter;

	SceneTransitionTestClass1(bool& FocusOnFlag_,int& FocusOnParameter_,bool& CallFlag_,char& EventParameter_):
		FocusOnFlag(FocusOnFlag_),
		FocusOnParameter(FocusOnParameter_),
		CallFlag(CallFlag_),
		EventParameter(EventParameter_)
	{}

	template<class T>
	void update(T& Manager){
		CallFlag=true;
	}

	UNDEFINED_EVENT_LISTENER;

	template<>
	void listenEvent<char>(){EventParameter=1;}

	template<>
	void listenEvent<MyEvent>(const MyEvent& e){
		//EventParameter=e;
	}

	template<>
	void listenEvent<char>(char e){
		EventParameter=e;
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
	char& EventParameter;
};

class SceneTransitionTestClass2{
public:
	typedef int Parameter;
	SceneTransitionTestClass2(bool& FocusOnFlag_,int& FocusOnParameter_,bool& CallFlag_,int& EventParameter_):
		FocusOnFlag(FocusOnFlag_),
		FocusOnParameter(FocusOnParameter_),
		CallFlag(CallFlag_),
		EventParameter(EventParameter_)
		{}

	template<class T>
	void update(T& Manager){
		CallFlag=true;
	}

	UNDEFINED_EVENT_LISTENER;

	template<>
	void listenEvent<int>(){EventParameter=-1;}

	template<>
	void listenEvent<int>(int e){EventParameter=e;}




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
	int& EventParameter;
};


typedef wing::scene_transition::SceneGroup<wing::scene_transition::SceneList<SceneTransitionTestClass1,SceneTransitionTestClass2> > MyManager;
	

//初期化テスト
TEST( Scene_Transition_Test, InitializeTest ){

	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;
	char EventParameter=0;
	int EventParameter1=0;
	auto Manager=MyManager(SceneTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1,EventParameter),SceneTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2,EventParameter1));
		

	EXPECT_EQ(0,Manager.getNowTarget()); 

	Manager.throwEvent<int>();

}

//パラメータなしのフォーカス変更テスト
TEST( Scene_Transition_Test, ChangeFocusTestNonParameter ){
 
	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;
	char EventParameter=0;
	int EventParameter1=0;
	auto Manager=MyManager(SceneTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1,EventParameter),SceneTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2,EventParameter1));
		

	Manager.changeFocus<SceneTransitionTestClass1>();
	EXPECT_EQ(0,Manager.getNowTarget()); 
	EXPECT_EQ(true,FocusOnFlag1); 
	EXPECT_EQ(false,FocusOnFlag2); 


	Manager.changeFocus<SceneTransitionTestClass2>();
	EXPECT_EQ(1,Manager.getNowTarget()); 
	EXPECT_EQ(false,FocusOnFlag1); 
	EXPECT_EQ(true,FocusOnFlag2); 


	Manager.changeFocus<SceneTransitionTestClass1>();
	EXPECT_EQ(0,Manager.getNowTarget()); 
	EXPECT_EQ(true,FocusOnFlag1); 
	EXPECT_EQ(false,FocusOnFlag2); 



}

//パラメータありのフォーカス変更テスト
TEST( Scene_Transition_Test, ChangeFocusTestParameter ){
 
	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;
	char EventParameter=0;
	int EventParameter1=0;
	auto Manager=MyManager(SceneTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1,EventParameter),SceneTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2,EventParameter1));
		
	


	Manager.changeFocus<SceneTransitionTestClass1>(10);
	EXPECT_EQ(0,Manager.getNowTarget()); 
	EXPECT_EQ(true,FocusOnFlag1); 
	EXPECT_EQ(false,FocusOnFlag2); 
	EXPECT_EQ(10,FocusOnParameter1); 

	
	Manager.changeFocus<SceneTransitionTestClass2>(4);
	EXPECT_EQ(1,Manager.getNowTarget()); 
	EXPECT_EQ(false,FocusOnFlag1); 
	EXPECT_EQ(true,FocusOnFlag2); 
	EXPECT_EQ(4,FocusOnParameter2);

	
	Manager.changeFocus<SceneTransitionTestClass1>(2);
	EXPECT_EQ(0,Manager.getNowTarget()); 
	EXPECT_EQ(true,FocusOnFlag1); 
	EXPECT_EQ(false,FocusOnFlag2); 
	EXPECT_EQ(2,FocusOnParameter1);
	

}


//Runのテスト
TEST( Scene_Transition_Test, RunTest ){

	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;
	char EventParameter=0;
	int EventParameter1=0;
	auto Manager=MyManager(SceneTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1,EventParameter),SceneTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2,EventParameter1));
		
	
	
	Manager.refresh();


	EXPECT_EQ(true,CallFlag1);
	EXPECT_EQ(false,CallFlag2); 

	Manager.changeFocus<SceneTransitionTestClass2>();
	Manager.refresh();
	EXPECT_EQ(false,CallFlag1);
	EXPECT_EQ(true,CallFlag2); 
}

//パラメータなしのイベントののテスト
TEST( Scene_Transition_Test, ThrowEventNonParameterTest ){
	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;
	char EventParameter=0;
	int EventParameter1=0;
	auto Manager=MyManager(SceneTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1,EventParameter),SceneTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2,EventParameter1));
		
	
	EXPECT_EQ(0,EventParameter);
	EXPECT_EQ(0,EventParameter1);

	Manager.throwEvent<char>();
	EXPECT_EQ(1,EventParameter); 
	EXPECT_EQ(0,EventParameter1);

	Manager.throwEvent<int>();
	EXPECT_EQ(1,EventParameter); 
	EXPECT_EQ(-1,EventParameter1);


}

//パラメータありのイベントのテスト
TEST( Scene_Transition_Test, ThrowEventParameterTest ){
	auto FocusOnFlag1=false;
	auto FocusOnFlag2=false;
	auto FocusOnParameter1=0;
	auto FocusOnParameter2=0;
	auto CallFlag1=false;
	auto CallFlag2=false;
	char EventParameter=0;
	int EventParameter1=0;
	auto Manager=MyManager(SceneTransitionTestClass1(FocusOnFlag1,FocusOnParameter1,CallFlag1,EventParameter),SceneTransitionTestClass2(FocusOnFlag2,FocusOnParameter2,CallFlag2,EventParameter1));
		
	EXPECT_EQ(0,EventParameter);
	EXPECT_EQ(0,EventParameter1);

	Manager.throwEvent<char>(4);
	EXPECT_EQ(4,EventParameter);
	EXPECT_EQ(0,EventParameter1);


	Manager.throwEvent<int>(3);
	EXPECT_EQ(4,EventParameter);
	EXPECT_EQ(3,EventParameter1);

	Manager.throwEvent<MyEvent>(MyEvent());


}