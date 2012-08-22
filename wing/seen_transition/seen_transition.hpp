/*******************************************************************************
                        シーンの移動を扱うためのクラス

Copyright (C) 2012 つららソフト


作成者  いかろ
動作環境 VC++ 2010 Express Edition
作成日時 2012/08/04 21:38
最終更新 2012/08/22 22:00

バージョン 0.999



<更新予定>
 ・ダイナミック版を作る
 

<概要>
WingLibraryの一部として提供され、
ゲーム内のシーンを統一的な方法で管理しやすくし、またその関係を構築することのできるテンプレートクラスです。
これを利用することによってシーンの移動を簡単に行うことができます。

<依存関係>
・外部
なし

・wing
helper.hpp

<クラス構成>
wing名前空間内のseen_transition名前空間内にまとめられています。
いくつかのクラスによって構成されていますが、クライアントが使用するクラスは
基本的にSeenGroupクラスのみです。

SeenGroupはいくつかのシーンをグループとしてまとめて管理するクラスで、個々のシーンを現すクラスは
テンプレート引数として渡します。

<クラスの動作及び相互作用>
SeenGroupのrunを呼ぶと自動的にフォーカスが入ったシーンオブジェクトが実行されます。

<使い方>
1.シーンをあらわす具体的なクラスを実装する。
暗黙のインターフェース(・が必須、*がオプション)は

*typedef (型) Parameter;
パラメータありのfocusOn(後述)が呼ばれたときの受け取る引数の型(複数受け取る場合はオブジェクト)

*void focusOn();
フォーカスが入ったとき呼ばれるコンストラクタのようなもの。
定義されていない場合はデフォルト(なにもしない)のものが呼ばれる。

*void focusOn(Parameter);
フォーカスが入ったとき呼ばれる(パラメータを受け取る)。


・template<class T> void run(T& Manager);
実行内容を書く。また、Managerへ参照を受け取れる(changeFocusを呼ぶため)

*void focusOut();
フォーカスが外れたときに呼ばれるデストラクタのようなもの。
定義されていない場合はデフォルトのものが呼ばれる

*template<> void catchEvent<受け取りたいイベントの型>()
パラメータなしのイベントを受け取るための特殊化

*template<> void catchEvent<受け取りたいイベントの型>(受け取りたいイベントの型 e)
パラメータありのイベントを受け取るための特殊化

となっています。
また、publicな領域に「UNDEFINED_EVENT_CHATCHER」マクロをおいてください。


2.SeenをSeenGroupのテンプレートパラメータとして渡す(typedefすること推奨)
※SeenGroup 変数名;という形で宣言すると関数宣言として扱われるようなので
auto GameManager = SeenGroup;
のような書き方をすること推奨。
また、コンストラクタの引数はテンプレートパラメータでわたしたクラスのオブジェクトを渡してください。

3.ループでManagerのrunを呼ぶ。




*******************************************************************************/


#pragma once
#include "helper.hpp"

								  


namespace wing{
namespace seen_transition{

template<typename T>
struct Traits;

template<int ID>
struct Dummy;


template < class Defalt, class S1, class S2, class S3, class S4, class S5, class S6,class S7, class S8, class S9, class S10, class S11, class S12, class S13, class S14, class S15,class S16, class S17, class S18, class S19>
struct SeenList;

class NoWaitFPSPolicy;

class NoRefreshPolicy;

struct default_policies;

template <class P>
struct FPSPolicy_is;

template <class P>
struct RefreshPolicy_is;


struct default_policy_args;

template <class P1, class P2>
struct policy_selector;

//========================================SeenGroup===================================


template <class SeenHolder, class P1=default_policy_args, class P2=default_policy_args >
class SeenGroup:public policy_selector<P1, P2>::FPSPolicy,
				  public policy_selector<P1, P2>::RefreshPolicy
	{
private:
	typedef typename policy_selector<P1, P2>::FPSPolicy FPSPolicy;
	typedef typename policy_selector<P1, P2>::RefreshPolicy RefreshPolicy;




	//changeFocusを特殊化をするため
	template<class T> struct ChangeFocusSpecialization;
	
	typedef typename SeenHolder::T0 Defalt;
	typedef typename SeenHolder::T1 U1;
	typedef typename SeenHolder::T2 U2;
	typedef typename SeenHolder::T3 U3;
	typedef typename SeenHolder::T4 U4;
	typedef typename SeenHolder::T5 U5;
	typedef typename SeenHolder::T6 U6;
	typedef typename SeenHolder::T7 U7;
	typedef typename SeenHolder::T8 U8;
	typedef typename SeenHolder::T9 U9;
	typedef typename SeenHolder::T10 U10;
	typedef typename SeenHolder::T11 U11;
	typedef typename SeenHolder::T12 U12;
	typedef typename SeenHolder::T13 U13;
	typedef typename SeenHolder::T14 U14;
	typedef typename SeenHolder::T15 U15;
	typedef typename SeenHolder::T16 U16;
	typedef typename SeenHolder::T17 U17;
	typedef typename SeenHolder::T18 U18;
	typedef typename SeenHolder::T19 U19;

public:

	SeenGroup(Defalt a, U1 a1=Dummy<1>(), U2 a2=Dummy<2>(), U3 a3=Dummy<3>(), U4 a4=Dummy<4>(), U5 a5=Dummy<5>(), U6 a6=Dummy<6>(), U7 a7=Dummy<7>(), U8 a8=Dummy<8>(), U9 a9=Dummy<9>(), U10 a10=Dummy<10>(), U11 a11=Dummy<11>(), U12 a12=Dummy<12>(), U13 a13=Dummy<13>(), U14 a14=Dummy<14>(), U15 a15=Dummy<15>(), U16 a16=Dummy<16>(), U17 a17=Dummy<17>(), U18 a18=Dummy<18>(), U19 a19=Dummy<19>());
	SeenGroup(const SeenGroup<SeenHolder,P1, P2>& Obj);
	SeenGroup& operator=(const SeenGroup<SeenHolder,P1, P2>& Obj);

	void run();
	int getNowTarget() const{return NowTarget;}
	
	//引数あり、なしの両方を提供
	template<class T>
		void changeFocus();
	template<class T>
		void changeFocus(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<T>::Result>::ParameterType p){ChangeFocusSpecialization<T>::func(p,*this);}
	
	template<class Event>
		void throwEvent();
	template<class Event>
		void throwEvent(typename wing::seen_transition::Traits<Event>::ParameterType e);


	template<> void changeFocus<Defalt>(){focusOut();NowTarget=0;CheckHasFocusOn::focusOn(obj0);}
	template<> void changeFocus<U1>(){focusOut();NowTarget=1;CheckHasFocusOn::focusOn(obj1);}
	template<> void changeFocus<U2>(){focusOut();NowTarget=2;CheckHasFocusOn::focusOn(obj2);}
	template<> void changeFocus<U3>(){focusOut();NowTarget=3;CheckHasFocusOn::focusOn(obj3);}
	template<> void changeFocus<U4>(){focusOut();NowTarget=4;CheckHasFocusOn::focusOn(obj4);}
	template<> void changeFocus<U5>(){focusOut();NowTarget=5;CheckHasFocusOn::focusOn(obj5);}
	template<> void changeFocus<U6>(){focusOut();NowTarget=6;CheckHasFocusOn::focusOn(obj6);}
	template<> void changeFocus<U7>(){focusOut();NowTarget=7;CheckHasFocusOn::focusOn(obj7);}
	template<> void changeFocus<U8>(){focusOut();NowTarget=8;CheckHasFocusOn::focusOn(obj8);}
	template<> void changeFocus<U9>(){focusOut();NowTarget=9;CheckHasFocusOn::focusOn(obj9);}
	template<> void changeFocus<U10>(){focusOut();NowTarget=10;CheckHasFocusOn::focusOn(obj10);}
	template<> void changeFocus<U11>(){focusOut();NowTarget=11;CheckHasFocusOn::focusOn(obj11);}
	template<> void changeFocus<U12>(){focusOut();NowTarget=12;CheckHasFocusOn::focusOn(obj12);}
	template<> void changeFocus<U13>(){focusOut();NowTarget=13;CheckHasFocusOn::focusOn(obj13);}
	template<> void changeFocus<U14>(){focusOut();NowTarget=14;CheckHasFocusOn::focusOn(obj14);}
	template<> void changeFocus<U15>(){focusOut();NowTarget=15;CheckHasFocusOn::focusOn(obj15);}
	template<> void changeFocus<U16>(){focusOut();NowTarget=16;CheckHasFocusOn::focusOn(obj16);}
	template<> void changeFocus<U17>(){focusOut();NowTarget=17;CheckHasFocusOn::focusOn(obj17);}
	template<> void changeFocus<U18>(){focusOut();NowTarget=18;CheckHasFocusOn::focusOn(obj18);}
	template<> void changeFocus<U19>(){focusOut();NowTarget=19;CheckHasFocusOn::focusOn(obj19);}
	

private:

	//フォーカスを変更するための補助関数
	void focusOut();

	int NowTarget;
	Defalt obj0;
	U1 obj1;
	U2 obj2;
	U3 obj3;
	U4 obj4;
	U5 obj5;
	U6 obj6;
	U7 obj7;
	U8 obj8;
	U9 obj9;
	U10 obj10;
	U11 obj11;
	U12 obj12;
	U13 obj13;
	U14 obj14;
	U15 obj15;
	U16 obj16;
	U17 obj17;
	U18 obj18;
	U19 obj19;

	template<class T>
	struct ChangeFocusSpecialization{
		//不正な変更をエラーにするためわざと提供しない
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<T>::Result>::ParameterType p,U& obj);
	};
	

	
	template<>
	struct ChangeFocusSpecialization<Defalt>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<Defalt>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=0;obj.obj0.focusOn(p);}
	};
	

	template<>
	struct ChangeFocusSpecialization<U1>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U1>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=1;obj.obj1.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U2>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U2>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=2;obj.obj2.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U3>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U3>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=3;obj.obj3.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U4>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U4>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=4;obj.obj4.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U5>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U5>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=5;obj.obj5.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U6>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U6>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=6;obj.obj6.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U7>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U7>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=7;obj.obj7.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U8>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U8>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=8;obj.obj8.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U9>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U9>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=9;obj.obj9.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U10>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U10>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=10;obj.obj10.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U11>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U11>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=11;obj.obj11.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U12>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U12>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=12;obj.obj12.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U13>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U13>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=13;obj.obj13.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U14>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U14>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=14;obj.obj14.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U15>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U15>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=15;obj.obj15.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U16>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U16>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=16;obj.obj16.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U17>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U17>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=17;obj.obj17.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U18>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U18>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=18;obj.obj18.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U19>{
		template<class U>
		static void func(typename Traits<typename wing::seen_transition::checkDefinedParameterTypedef<U19>::Result>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=19;obj.obj19.focusOn(p);}
	};


};



}
}




//==================================method 実装====================================

//コンストラクタ
template <class SeenHolder, class P1, class P2 >
wing::seen_transition::SeenGroup<SeenHolder,P1, P2>::
SeenGroup(Defalt a, U1 a1, U2 a2, U3 a3, U4 a4, U5 a5, U6 a6, U7 a7, U8 a8, U9 a9, U10 a10, U11 a11, U12 a12, U13 a13, U14 a14, U15 a15, U16 a16, U17 a17, U18 a18, U19 a19):
		NowTarget(0),
		obj0(a),
		obj1(a1),
		obj2(a2),
		obj3(a3),
		obj4(a4),
		obj5(a5),
		obj6(a6),
		obj7(a7),
		obj8(a8),
		obj9(a9),
		obj10(a10),
		obj11(a11),
		obj12(a12),
		obj13(a13),
		obj14(a14),
		obj15(a15),
		obj16(a16),
		obj17(a17),
		obj18(a18),
		obj19(a19)
	{
		CheckHasFocusOn::focusOn(obj0);
	}


//コピーコンストラクタ
template <class SeenHolder, class P1, class P2 >
wing::seen_transition::SeenGroup<SeenHolder,P1, P2>::SeenGroup(const SeenGroup<SeenHolder,P1, P2>& Obj){
	Obj.obj0=obj0;
	Obj.obj1=obj1;
	Obj.obj2=obj2;
	Obj.obj3=obj3;
	Obj.obj4=obj4;
	Obj.obj5=obj5;
	Obj.obj6=obj6;
	Obj.obj7=obj7;
	Obj.obj8=obj8;
	Obj.obj9=obj9;
	Obj.obj10=obj10;
	Obj.obj11=obj11;
	Obj.obj12=obj12;
	Obj.obj13=obj13;
	Obj.obj14=obj14;
	Obj.obj15=obj15;
	Obj.obj16=obj16;
	Obj.obj17=obj17;
	Obj.obj18=obj18;
	Obj.obj19=obj19;
}

//代入演算子
template <class SeenHolder, class P1, class P2 >
wing::seen_transition::SeenGroup<SeenHolder,P1, P2>& wing::seen_transition::SeenGroup<SeenHolder,P1, P2>::operator=(const SeenGroup<SeenHolder,P1, P2>& Obj){
	Obj.obj0=obj0;
	Obj.obj1=obj1;
	Obj.obj2=obj2;
	Obj.obj3=obj3;
	Obj.obj4=obj4;
	Obj.obj5=obj5;
	Obj.obj6=obj6;
	Obj.obj7=obj7;
	Obj.obj8=obj8;
	Obj.obj9=obj9;
	Obj.obj10=obj10;
	Obj.obj11=obj11;
	Obj.obj12=obj12;
	Obj.obj13=obj13;
	Obj.obj14=obj14;
	Obj.obj15=obj15;
	Obj.obj16=obj16;
	Obj.obj17=obj17;
	Obj.obj18=obj18;
	Obj.obj19=obj19;
}


//throwEvent
template <class SeenHolder, class P1, class P2 >
template<class Event>
void wing::seen_transition::SeenGroup<SeenHolder,P1, P2>::throwEvent(){
	obj0.catchEvent<Event>();
	obj1.catchEvent<Event>();
	obj2.catchEvent<Event>();
	obj3.catchEvent<Event>();
	obj4.catchEvent<Event>();
	obj5.catchEvent<Event>();
	obj6.catchEvent<Event>();
	obj7.catchEvent<Event>();
	obj8.catchEvent<Event>();
	obj9.catchEvent<Event>();
	obj10.catchEvent<Event>();
	obj11.catchEvent<Event>();
	obj12.catchEvent<Event>();
	obj13.catchEvent<Event>();
	obj14.catchEvent<Event>();
	obj15.catchEvent<Event>();
	obj16.catchEvent<Event>();
	obj17.catchEvent<Event>();
	obj18.catchEvent<Event>();
	obj19.catchEvent<Event>();
}

template <class SeenHolder, class P1, class P2 >
template<class Event>
void wing::seen_transition::SeenGroup<SeenHolder,P1, P2>::throwEvent(typename wing::seen_transition::Traits<Event>::ParameterType e){
	obj0.catchEvent<Event>(e);
	obj1.catchEvent<Event>(e);
	obj2.catchEvent<Event>(e);
	obj3.catchEvent<Event>(e);
	obj4.catchEvent<Event>(e);
	obj5.catchEvent<Event>(e);
	obj6.catchEvent<Event>(e);
	obj7.catchEvent<Event>(e);
	obj8.catchEvent<Event>(e);
	obj9.catchEvent<Event>(e);
	obj10.catchEvent<Event>(e);
	obj11.catchEvent<Event>(e);
	obj12.catchEvent<Event>(e);
	obj13.catchEvent<Event>(e);
	obj14.catchEvent<Event>(e);
	obj15.catchEvent<Event>(e);
	obj16.catchEvent<Event>(e);
	obj17.catchEvent<Event>(e);
	obj18.catchEvent<Event>(e);
	obj19.catchEvent<Event>(e);
}



template <class SeenHolder, class P1, class P2 >
void wing::seen_transition::SeenGroup<SeenHolder,P1, P2>::
	run(){
	
	DrawStart();

	switch(NowTarget){
		case 0:
			obj0.run(*this);
			break;
		case 1:
			obj1.run(*this);
			break;
		case 2:
			obj2.run(*this);
			break;
		case 3:
			obj3.run(*this);
			break;
		case 4:
			obj4.run(*this);
			break;
		case 5:
			obj5.run(*this);
			break;
		case 6:
			obj6.run(*this);
			break;
		case 7:
			obj7.run(*this);
			break;
		case 8:
			obj8.run(*this);
			break;
		case 9:
			obj9.run(*this);
			break;
		case 10:
			obj10.run(*this);
			break;
		case 11:
			obj11.run(*this);
			break;
		case 12:
			obj12.run(*this);
			break;
		case 13:
			obj13.run(*this);
			break;
		case 14:
			obj14.run(*this);
			break;
		case 15:
			obj15.run(*this);
			break;
		case 16:
			obj16.run(*this);
			break;
		case 17:
			obj17.run(*this);
			break;
		case 18:
			obj18.run(*this);
			break;
		case 19:
			obj19.run(*this);
			break;	
	}

	}

template <class SeenHolder, class P1, class P2 >
void wing::seen_transition::SeenGroup<SeenHolder,P1, P2>::
	focusOut(){
		switch(NowTarget){
			case 0:
				CheckHasFocusOut::focusOut(obj0);
				break;
			case 1:
				CheckHasFocusOut::focusOut(obj1);
				break;
			case 2:
				CheckHasFocusOut::focusOut(obj2);
				break;
			case 3:
				CheckHasFocusOut::focusOut(obj3);
				break;
			case 4:
				CheckHasFocusOut::focusOut(obj4);
				break;
			case 5:
				CheckHasFocusOut::focusOut(obj5);
				break;
			case 6:
				CheckHasFocusOut::focusOut(obj6);
				break;
			case 7:
				CheckHasFocusOut::focusOut(obj7);
				break;
			case 8:
				CheckHasFocusOut::focusOut(obj8);
				break;
			case 9:
				CheckHasFocusOut::focusOut(obj9);
				break;
			case 10:
				CheckHasFocusOut::focusOut(obj10);
				break;
			case 11:
				CheckHasFocusOut::focusOut(obj11);
				break;
			case 12:
				CheckHasFocusOut::focusOut(obj12);
				break;
			case 13:
				CheckHasFocusOut::focusOut(obj13);
				break;
			case 14:
				CheckHasFocusOut::focusOut(obj14);
				break;
			case 15:
				CheckHasFocusOut::focusOut(obj15);
				break;
			case 16:
				CheckHasFocusOut::focusOut(obj16);
				break;
			case 17:
				CheckHasFocusOut::focusOut(obj17);
				break;
			case 18:
				CheckHasFocusOut::focusOut(obj18);
				break;
			case 19:
				CheckHasFocusOut::focusOut(obj19);
				break;
		}
	DrawFinish();
	wait();

	}
