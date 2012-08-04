/*******************************************************************************
                        シーンの移動を扱うためのクラス

Copyright (C) 2012 つららソフト


作成者  いかろ
動作環境 VC++ 2010 Express Edition
作成日時 2012/08/04 21:38
最終更新 2012/08/04 21:38
バージョン 0.9

<更新履歴>
 ・2012/08/04 21:38
	暫定版完成
<更新予定>
 ・FPS自動調整機能追加
 ・イベント管理追加

<概要>
WingLibraryの一部として提供され、
ゲーム内のシーンを統一的な方法で管理しやすくし、またその関係を構築することのできるテンプレートクラスです。
これを利用することによってシーンの移動を簡単に行うことができます。

<依存関係>
なし

<クラス構成>
wing名前空間内のseen_transition名前空間内にまとめられています。
いくつかのクラスによって構成されていますが、クライアントが使用するクラスは
基本的にSeenManagerクラスのみです。

SeenManagerはシーンを管理するクラスで、シーンを現すクラスは
テンプレート引数として渡します。

<クラスの動作及び相互作用>
SeenManagerのrunを呼ぶと自動的にフォーカスが入ったオブジェクトが実行されます。

<使い方>
1.シーンをあらわす具体的なクラスを実装する。
暗黙のインターフェースは

・typedef (型) Parameter;
パラメータありのfocusOn(後述)が呼ばれたときの受け取る引数の方(複数受け取る場合はオブジェクト)

・void focusOn();
フォーカスが入ったとき呼ばれる

・void focusOn(Parameter);
フォーカスが入ったとき呼ばれる(パラメータを受け取る)

・template<class T> void run(T& Manager);
実行内容を書く。また、Managerへ参照を受け取れる(changeFocusを呼ぶため)

・void focusOut();
//フォーカスが外れたときに呼ばれる

となっています。

2.SeenをSeenManagerのテンプレートパラメータとして渡す(typedefすること推奨)
※SeenManager 変数名;という形で宣言すると関数宣言として扱われるようなので
auto GameManager = SeenManager;
のような書き方をすること推奨。
また、コンストラクタの引数はテンプレートパラメータでわたしたクラスのオブジェクトを渡してください。

3.ループでManagerのrunを呼ぶ。




*******************************************************************************/



#pragma once

namespace wing{
namespace seen_transition{


//==================================Traits=====================================
//SeenManagerのchangeForcusのための型特性。
template<typename T>struct Traits{typedef T& ParameterType;};
template<typename T>struct Traits<T*>{typedef T* ParameterType;};
template<typename T>struct Traits<T&>{typedef T& ParameterType;};
template<> struct Traits<bool>{typedef bool ParameterType;};
template<> struct Traits<char>{typedef char ParameterType;};
template<> struct Traits<unsigned char>{typedef unsigned char ParameterType;};
template<> struct Traits<short>{typedef short ParameterType;};
template<> struct Traits<unsigned short>{typedef unsigned  short ParameterType;};
template<> struct Traits<int>{typedef int ParameterType;};
template<> struct Traits<unsigned int>{typedef unsigned  int ParameterType;};
template<> struct Traits<long>{typedef long ParameterType;};
template<> struct Traits<unsigned long>{typedef unsigned ParameterType;};
template<> struct Traits<float>{typedef float ParameterType;};
template<> struct Traits<double>{typedef double ParameterType;};
template<> struct Traits<long double>{typedef long double ParameterType;};


//==================================Dummy=====================================
//SeenManagerにデフォルト引数として渡すためのダミー
//focusOnを提供していないのはDummyにfocusを入れることは不正なため
template<int ID>
struct Dummy{
	typedef int Parameter;
	
	template<class T>
	void run(T& Manager){}
	void focusOut(){}
};


//========================================SeenManager===================================

template < class Defalt,class U1=Dummy<1>,class U2=Dummy<2>,class U3=Dummy<3>,class U4=Dummy<4>,class U5=Dummy<5>,class U6=Dummy<6>,class U7=Dummy<7>,class U8=Dummy<8>,class U9=Dummy<9>,class U10=Dummy<10>,class U11=Dummy<11>,class U12=Dummy<12>,class U13=Dummy<13>,class U14=Dummy<14>,class U15=Dummy<15>,class U16=Dummy<16>,class U17=Dummy<17>,class U18=Dummy<18>,class U19=Dummy<19> >
class SeenManager{
private:
	//changeFocusを特殊化をするため
	template<class T> struct ChangeFocusSpecialization;

public:

	SeenManager(Defalt a, U1 a1=Dummy<1>(), U2 a2=Dummy<2>(), U3 a3=Dummy<3>(), U4 a4=Dummy<4>(), U5 a5=Dummy<5>(), U6 a6=Dummy<6>(), U7 a7=Dummy<7>(), U8 a8=Dummy<8>(), U9 a9=Dummy<9>(), U10 a10=Dummy<10>(), U11 a11=Dummy<11>(), U12 a12=Dummy<12>(), U13 a13=Dummy<13>(), U14 a14=Dummy<14>(), U15 a15=Dummy<15>(), U16 a16=Dummy<16>(), U17 a17=Dummy<17>(), U18 a18=Dummy<18>(), U19 a19=Dummy<19>());
	void run();
	int getNowTarget() const{return NowTarget;}
	
	//引数あり、なしの両方を提供
	template<class T>void changeFocus();
	template<class T>void changeFocus(typename Traits<typename T::Parameter>::ParameterType p){ChangeFocusSpecialization<T>::func(p,*this);}
	
	

	template<> void changeFocus<Defalt>(){focusOut();NowTarget=0;obj0.focusOn();}
	template<> void changeFocus<U1>(){focusOut();NowTarget=1;obj1.focusOn();}
	template<> void changeFocus<U2>(){focusOut();NowTarget=2;obj2.focusOn();}
	template<> void changeFocus<U3>(){focusOut();NowTarget=3;obj3.focusOn();}
	template<> void changeFocus<U4>(){focusOut();NowTarget=4;obj4.focusOn();}
	template<> void changeFocus<U5>(){focusOut();NowTarget=5;obj5.focusOn();}
	template<> void changeFocus<U6>(){focusOut();NowTarget=6;obj6.focusOn();}
	template<> void changeFocus<U7>(){focusOut();NowTarget=7;obj7.focusOn();}
	template<> void changeFocus<U8>(){focusOut();NowTarget=8;obj8.focusOn();}
	template<> void changeFocus<U9>(){focusOut();NowTarget=9;obj9.focusOn();}
	template<> void changeFocus<U10>(){focusOut();NowTarget=10;obj10.focusOn();}
	template<> void changeFocus<U11>(){focusOut();NowTarget=11;obj11.focusOn();}
	template<> void changeFocus<U12>(){focusOut();NowTarget=12;obj12.focusOn();}
	template<> void changeFocus<U13>(){focusOut();NowTarget=13;obj13.focusOn();}
	template<> void changeFocus<U14>(){focusOut();NowTarget=14;obj14.focusOn();}
	template<> void changeFocus<U15>(){focusOut();NowTarget=15;obj15.focusOn();}
	template<> void changeFocus<U16>(){focusOut();NowTarget=16;obj16.focusOn();}
	template<> void changeFocus<U17>(){focusOut();NowTarget=17;obj17.focusOn();}
	template<> void changeFocus<U18>(){focusOut();NowTarget=18;obj18.focusOn();}
	template<> void changeFocus<U19>(){focusOut();NowTarget=19;obj19.focusOn();}
	

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
		static void func(typename Traits<typename T::Parameter>::ParameterType p,U& obj);
	};
	
	
	template<>
	struct ChangeFocusSpecialization<Defalt>{
		template<class U>
		static void func(typename Traits<typename Defalt::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=0;obj.obj0.focusOn(p);}
	};
	

	template<>
	struct ChangeFocusSpecialization<U1>{
		template<class U>
		static void func(typename Traits<typename U1::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=1;obj.obj1.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U2>{
		template<class U>
		static void func(typename Traits<typename U2::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=2;obj.obj2.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U3>{
		template<class U>
		static void func(typename Traits<typename U3::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=3;obj.obj3.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U4>{
		template<class U>
		static void func(typename Traits<typename U4::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=4;obj.obj4.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U5>{
		template<class U>
		static void func(typename Traits<typename U5::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=5;obj.obj5.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U6>{
		template<class U>
		static void func(typename Traits<typename U6::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=6;obj.obj6.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U7>{
		template<class U>
		static void func(typename Traits<typename U7::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=7;obj.obj7.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U8>{
		template<class U>
		static void func(typename Traits<typename U8::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=8;obj.obj8.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U9>{
		template<class U>
		static void func(typename Traits<typename U9::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=9;obj.obj9.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U10>{
		template<class U>
		static void func(typename Traits<typename U10::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=10;obj.obj10.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U11>{
		template<class U>
		static void func(typename Traits<typename U11::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=11;obj.obj11.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U12>{
		template<class U>
		static void func(typename Traits<typename U12::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=12;obj.obj12.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U13>{
		template<class U>
		static void func(typename Traits<typename U13::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=13;obj.obj13.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U14>{
		template<class U>
		static void func(typename Traits<typename U14::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=14;obj.obj14.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U15>{
		template<class U>
		static void func(typename Traits<typename U15::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=15;obj.obj15.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U16>{
		template<class U>
		static void func(typename Traits<typename U16::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=16;obj.obj16.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U17>{
		template<class U>
		static void func(typename Traits<typename U17::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=17;obj.obj17.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U18>{
		template<class U>
		static void func(typename Traits<typename U18::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=18;obj.obj18.focusOn(p);}
	};

	template<>
	struct ChangeFocusSpecialization<U19>{
		template<class U>
		static void func(typename Traits<typename U19::Parameter>::ParameterType p,U& obj){obj.focusOut();obj.NowTarget=19;obj.obj19.focusOn(p);}
	};


};



}
}




//==================================method 実装====================================


template < class Defalt,class U1,class U2,class U3,class U4,class U5,class U6,class U7,class U8,class U9,class U10,class U11,class U12,class U13,class U14,class U15,class U16,class U17,class U18,class U19>
wing::seen_transition::SeenManager<Defalt,U1,U2,U3,U4,U5,U6,U7,U8,U9,U10,U11,U12,U13,U14,U15,U16,U17,U18,U19>::
SeenManager(Defalt a, U1 a1, U2 a2, U3 a3, U4 a4, U5 a5, U6 a6, U7 a7, U8 a8, U9 a9, U10 a10, U11 a11, U12 a12, U13 a13, U14 a14, U15 a15, U16 a16, U17 a17, U18 a18, U19 a19):
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
	}

template < class Defalt,class U1,class U2,class U3,class U4,class U5,class U6,class U7,class U8,class U9,class U10,class U11,class U12,class U13,class U14,class U15,class U16,class U17,class U18,class U19>
void wing::seen_transition::SeenManager<Defalt,U1,U2,U3,U4,U5,U6,U7,U8,U9,U10,U11,U12,U13,U14,U15,U16,U17,U18,U19>::
	run(){
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

template < class Defalt,class U1,class U2,class U3,class U4,class U5,class U6,class U7,class U8,class U9,class U10,class U11,class U12,class U13,class U14,class U15,class U16,class U17,class U18,class U19>
void wing::seen_transition::SeenManager<Defalt,U1,U2,U3,U4,U5,U6,U7,U8,U9,U10,U11,U12,U13,U14,U15,U16,U17,U18,U19>::
	focusOut(){
		switch(NowTarget){
			case 0:
				obj0.focusOut();
				break;
			case 1:
				obj1.focusOut();
				break;
			case 2:
				obj2.focusOut();
				break;
			case 3:
				obj3.focusOut();
				break;
			case 4:
				obj4.focusOut();
				break;
			case 5:
				obj5.focusOut();
				break;
			case 6:
				obj6.focusOut();
				break;
			case 7:
				obj7.focusOut();
				break;
			case 8:
				obj8.focusOut();
				break;
			case 9:
				obj9.focusOut();
				break;
			case 10:
				obj10.focusOut();
				break;
			case 11:
				obj11.focusOut();
				break;
			case 12:
				obj12.focusOut();
				break;
			case 13:
				obj13.focusOut();
				break;
			case 14:
				obj14.focusOut();
				break;
			case 15:
				obj15.focusOut();
				break;
			case 16:
				obj16.focusOut();
				break;
			case 17:
				obj17.focusOut();
				break;
			case 18:
				obj18.focusOut();
				break;
			case 19:
				obj19.focusOut();
				break;
		}	
	}
