#pragma once
#pragma warning( disable : 4100 )
#pragma warning( disable : 4290 )


#include <string>
#include <memory>
#include <unordered_map>
#include <stdexcept>

#include "../common.hpp"


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


//Parameter��Typedef����`����Ă��邩�ɂ���ēK�؂Ȍ^��Ԃ�
template<class TargetClass>
class checkDefinedParameterTypedef{
private:
	template<typename T>
	static typename T::Parameter check(typename T::Parameter*);
	template<typename>
	static wing::NullType check(...);
public:
	typedef decltype(check<TargetClass>(nullptr)) Result;

};


//==================================Dummy=====================================
//SeenManager�Ƀf�t�H���g�����Ƃ��ēn�����߂̃_�~�[
//focusOn��񋟂��Ă��Ȃ��̂�Dummy��focus�����邱�Ƃ͕s���Ȃ���
template<int ID>
struct Dummy{
	
	template<class T>
	void run(T& Manager){}
	template<class Event> void catchEvent(){}
	template<class Event> void catchEvent(Event& e){}

	void focusOut(){}
	
};

//================================SeenList===================================
template < class Defalt,class S1=Dummy<1>,class S2=Dummy<2>,class S3=Dummy<3>,class S4=Dummy<4>,class S5=Dummy<5>,class S6=Dummy<6>,class S7=Dummy<7>,class S8=Dummy<8>,class S9=Dummy<9>,class S10=Dummy<10>,class S11=Dummy<11>,class S12=Dummy<12>,class S13=Dummy<13>,class S14=Dummy<14>,class S15=Dummy<15>,class S16=Dummy<16>,class S17=Dummy<17>,class S18=Dummy<18>,class S19=Dummy<19> >
struct SeenList{
	typedef Defalt T0;
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


//====================DefaultSeenContainerSafetyPolicy==================
template<class Seen,class Key>
class DefaultSeenContainerSafetyPolicy{
public:
	typedef std::shared_ptr<Seen> SeenPointee;

	void append(std::shared_ptr<Seen> AppendSeen, Key AppendKey)throw(std::invalid_argument){
		if (SeenData.find(AppendKey)==SeenData.end()){
			SeenData[AppendKey]=AppendSeen;
		}else{
			throw std::invalid_argument("���łɓ����L�[�̃I�u�W�F�N�g���ǉ�����Ă���");
		}
	}

protected:
	SeenPointee get(Key Key_)throw(std::invalid_argument){
		if (SeenData.find(AppendKey)!=SeenData.end()){
			return SeenData[Key_];
		}else{
			throw std::invalid_argument("�L�[�����݂��Ȃ�");
		}
	}

private:
	std::unordered_map<Key,SeenPointee> SeenData;
	
};



}
}