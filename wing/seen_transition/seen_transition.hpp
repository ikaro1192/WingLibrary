/*******************************************************************************
                        �V�[���̈ړ����������߂̃N���X

Copyright (C) 2012 ���\�t�g


�쐬��  ������
����� VC++ 2010 Express Edition
�쐬���� 2012/08/04 21:38
�ŏI�X�V 2012/08/09 22:37

�o�[�W���� 0.9

<�X�V����>
 �E2012/08/04 21:38
	�b��Ŋ���
 �E2012/08/09 22:37
	Policy�������ǉ�
	����ɔ����e���v���[�g�����ύX
 �E2012/08/13 21:48
	Event�@�\�ǉ�
 �E2012/08/10 22:37
	���O���e���v���[�g�����ɕύX


<�X�V�\��>
 �E�_�C�i�~�b�N�ł����

<�T�v>
WingLibrary�̈ꕔ�Ƃ��Ē񋟂���A
�Q�[�����̃V�[���𓝈�I�ȕ��@�ŊǗ����₷�����A�܂����̊֌W���\�z���邱�Ƃ̂ł���e���v���[�g�N���X�ł��B
����𗘗p���邱�Ƃɂ���ăV�[���̈ړ����ȒP�ɍs�����Ƃ��ł��܂��B

<�ˑ��֌W>
�Ȃ�

<�N���X�\��>
wing���O��ԓ���seen_transition���O��ԓ��ɂ܂Ƃ߂��Ă��܂��B
�������̃N���X�ɂ���č\������Ă��܂����A�N���C�A���g���g�p����N���X��
��{�I��SeenManager�N���X�݂̂ł��B

SeenManager�̓V�[�����Ǘ�����N���X�ŁA�V�[���������N���X��
�e���v���[�g�����Ƃ��ēn���܂��B

<�N���X�̓���y�ё��ݍ�p>
SeenManager��run���ĂԂƎ����I�Ƀt�H�[�J�X���������I�u�W�F�N�g�����s����܂��B

<�g����>
1.�V�[��������킷��̓I�ȃN���X����������B
�Öق̃C���^�[�t�F�[�X��

�Etypedef (�^) Parameter;
�p�����[�^�����focusOn(��q)���Ă΂ꂽ�Ƃ��̎󂯎������̕�(�����󂯎��ꍇ�̓I�u�W�F�N�g)

�Evoid focusOn();
�t�H�[�J�X���������Ƃ��Ă΂��

�Evoid focusOn(Parameter);
�t�H�[�J�X���������Ƃ��Ă΂��(�p�����[�^���󂯎��)

�Etemplate<class Event> void catchEvent(){}
�C�x���g�������Ă����Ƃ��ɓK�����Ȃ��ꍇ�������邽��(�C�x���g���E���ꍇ�͓��ꉻ���Ă�������)


�Etemplate<class T> void run(T& Manager);
���s���e�������B�܂��AManager�֎Q�Ƃ��󂯎���(changeFocus���ĂԂ���)

�Evoid focusOut();
//�t�H�[�J�X���O�ꂽ�Ƃ��ɌĂ΂��

�ƂȂ��Ă��܂��B

2.Seen��SeenManager�̃e���v���[�g�p�����[�^�Ƃ��ēn��(typedef���邱�Ɛ���)
��SeenManager �ϐ���;�Ƃ����`�Ő錾����Ɗ֐��錾�Ƃ��Ĉ�����悤�Ȃ̂�
auto GameManager = SeenManager;
�̂悤�ȏ����������邱�Ɛ����B
�܂��A�R���X�g���N�^�̈����̓e���v���[�g�p�����[�^�ł킽�����N���X�̃I�u�W�F�N�g��n���Ă��������B

3.���[�v��Manager��run���ĂԁB




*******************************************************************************/



#pragma once

namespace wing{
namespace seen_transition{


//================================FPS Policy===================================

template<int FPS>
class StaticFPSPolicy{
public:

	void wait();

private:


};


//==================================Traits=====================================
//SeenManager��changeForcus�̂��߂̌^�����B
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
//SeenManager�Ƀf�t�H���g�����Ƃ��ēn�����߂̃_�~�[
//focusOn��񋟂��Ă��Ȃ��̂�Dummy��focus�����邱�Ƃ͕s���Ȃ���
template<int ID>
struct Dummy{
	typedef int Parameter;
	
	template<class T>
	void run(T& Manager){}
	template<class Event> void catchEvent(){}
	void focusOut(){}
	
};

template < class S0,class S1=Dummy<1>,class S2=Dummy<2>,class S3=Dummy<3>,class S4=Dummy<4>,class S5=Dummy<5>,class S6=Dummy<6>,class S7=Dummy<7>,class S8=Dummy<8>,class S9=Dummy<9>,class S10=Dummy<10>,class S11=Dummy<11>,class S12=Dummy<12>,class S13=Dummy<13>,class S14=Dummy<14>,class S15=Dummy<15>,class S16=Dummy<16>,class S17=Dummy<17>,class S18=Dummy<18>,class S19=Dummy<19> >
struct Seen{
	typedef S0 T0;
	typedef S1 T1;
	typedef S2 T2;
	typedef S3 T3;
	typedef S4 T4;
	typedef S5 T5;
	typedef S6 T6;
	typedef S7 T7;
	typedef S8 T8;
	typedef S9 T9;
	typedef S10 T10;
	typedef S11 T11;
	typedef S12 T12;
	typedef S13 T13;
	typedef S14 T14;
	typedef S15 T15;
	typedef S16 T16;
	typedef S17 T17;
	typedef S18 T18;
	typedef S19 T19;
};



class NoWaitFPSPolicy{
public:
	void wait(){}

};

class NoRefreshPolicy{
public:
	void DrawStart(){}
	void DrawFinish(){}


};


//==============================���O�t���e���v���[�g�p�����[�^===============================
struct default_policies{
  typedef NoWaitFPSPolicy FPSPolicy;
  typedef NoRefreshPolicy RefreshPolicy;
};

template <class P>
struct FPSPolicy_is : virtual default_policies{
	typedef P FPSPolicy;
};

template <class P>
struct RefreshPolicy_is : virtual default_policies{
	typedef P RefreshPolicy;
};

struct default_policy_args : virtual default_policies{};

template <class Base, int D>
struct discriminator : public Base {};

template <class P1, class P2>
struct policy_selector
  : discriminator<P1, 1>, discriminator<P2, 2>{};



//========================================SeenManager===================================

//Parameter��Null�̂Ƃ��ɖ����I�Ɏg���B
class NullType{};

template <class SeenHolder, class P1=default_policy_args, class P2=default_policy_args >
class SeenManager:public policy_selector<P1, P2>::FPSPolicy,
				  public policy_selector<P1, P2>::RefreshPolicy
	{
private:
	typedef typename policy_selector<P1, P2>::FPSPolicy FPSPolicy;
	typedef typename policy_selector<P1, P2>::RefreshPolicy RefreshPolicy;


	//changeFocus����ꉻ�����邽��
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

	SeenManager(Defalt a, U1 a1=Dummy<1>(), U2 a2=Dummy<2>(), U3 a3=Dummy<3>(), U4 a4=Dummy<4>(), U5 a5=Dummy<5>(), U6 a6=Dummy<6>(), U7 a7=Dummy<7>(), U8 a8=Dummy<8>(), U9 a9=Dummy<9>(), U10 a10=Dummy<10>(), U11 a11=Dummy<11>(), U12 a12=Dummy<12>(), U13 a13=Dummy<13>(), U14 a14=Dummy<14>(), U15 a15=Dummy<15>(), U16 a16=Dummy<16>(), U17 a17=Dummy<17>(), U18 a18=Dummy<18>(), U19 a19=Dummy<19>());
	void run();
	int getNowTarget() const{return NowTarget;}
	
	//��������A�Ȃ��̗������
	template<class T>
		void changeFocus();
	template<class T>
		void changeFocus(typename Traits<typename T::Parameter>::ParameterType p){ChangeFocusSpecialization<T>::func(p,*this);}
	
	template<class Event>
		void throwEvent();
	template<class Event>
		void throwEvent(Event& e);


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

	//�t�H�[�J�X��ύX���邽�߂̕⏕�֐�
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
		//�s���ȕύX���G���[�ɂ��邽�߂킴�ƒ񋟂��Ȃ�
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




//==================================method ����====================================


template <class SeenHolder, class P1, class P2 >
template<class Event>
void wing::seen_transition::SeenManager<SeenHolder,P1, P2>::throwEvent(){
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
void wing::seen_transition::SeenManager<SeenHolder,P1, P2>::throwEvent(Event& e){
	obj0.catchEvent<Event>(Event& e);
	obj1.catchEvent<Event>(Event& e);
	obj2.catchEvent<Event>(Event& e);
	obj3.catchEvent<Event>(Event& e);
	obj4.catchEvent<Event>(Event& e);
	obj5.catchEvent<Event>(Event& e);
	obj6.catchEvent<Event>(Event& e);
	obj7.catchEvent<Event>(Event& e);
	obj8.catchEvent<Event>(Event& e);
	obj9.catchEvent<Event>(Event& e);
	obj10.catchEvent<Event>(Event& e);
	obj11.catchEvent<Event>(Event& e);
	obj12.catchEvent<Event>(Event& e);
	obj13.catchEvent<Event>(Event& e);
	obj14.catchEvent<Event>(Event& e);
	obj15.catchEvent<Event>(Event& e);
	obj16.catchEvent<Event>(Event& e);
	obj17.catchEvent<Event>(Event& e);
	obj18.catchEvent<Event>(Event& e);
	obj19.catchEvent<Event>(Event& e);
}


template <class SeenHolder, class P1, class P2 >
wing::seen_transition::SeenManager<SeenHolder,P1, P2>::
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

template <class SeenHolder, class P1, class P2 >
void wing::seen_transition::SeenManager<SeenHolder,P1, P2>::
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
void wing::seen_transition::SeenManager<SeenHolder,P1, P2>::
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
	DrawFinish();
	wait();

	}
