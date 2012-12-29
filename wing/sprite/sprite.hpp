#pragma once
#pragma warning(disable:4481)

#include<memory>
#include<vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <type_traits>
#include <string.h>

#include "wing\common.hpp"
#include "wing\utility\utility.hpp"

namespace wing{
namespace canvas{
template<class T>
class AbstructCanvas;	
}
}

namespace wing{
namespace image{
class DrawEngine;
	
}}


namespace wing{

/**
*@brief Sprite�Ɋ֌W����Sprite�N���X�Ɠ����蔻��֐��Q
*/
namespace sprite{


//�����蔻��n�̊֐�
/**
*@brief ��`���m(Sprite��z��)�̓����蔻��
*@param obj1 �����蔻����s���I�u�W�F�N�g1
*@param obj2 �����蔻����s���I�u�W�F�N�g2
*@return �������Ă����true�B�������Ă��Ȃ��A�������g�̏ꍇfalse
**/
template<class A, class B>
bool checkRectHit(const A& obj1, const B& obj2);

/**
*@brief �~���m(Sprite��z��)�̓����蔻��
*@param obj1 �����蔻����s���I�u�W�F�N�g1
*@param obj2 �����蔻����s���I�u�W�F�N�g2
*@return �������Ă����true�B�������Ă��Ȃ��A�������g�̏ꍇfalse
**/
template<class A, class B>
inline bool checkCircleHit(const A& obj1, const B& obj2);

/**
*@brief �ړ�(1�t���[���O�̈ʒu)���l�����������x�ȉ~���m(Sprite��z��)�̓����蔻��
*@param obj1 �����蔻����s���I�u�W�F�N�g1
*@param obj2 �����蔻����s���I�u�W�F�N�g2
*@return �������Ă����true�B�������Ă��Ȃ��A�������g�̏ꍇfalse
**/
template<class A, class B>
inline bool checkAccuracyCircleHit(const A& obj1, const B& obj2);

/**
*@brief �X�v���C�g�����t���b�V������
*@param Canvas ���肷��L�����o�X
*@param begin
*@param end iterator
*@param remover ���񂾃X�v���C�g�ɓK������or��菜���������s���t�@���N�^
*@return remover�̌���
**/
template<class RemovePolicy,class CanvasClass,class Iter>
inline Iter refreshSprite(CanvasClass& Canvas, Iter begin, Iter end);

struct NoRemove{

template<class Iter,class Function>
static Iter remove(Iter&,Iter& end,Function){return end;}
};

struct Remove{
template<class Iter,class Function>
static Iter remove(Iter& begin, Iter& end,Function func){return std::remove_if(begin,end,func);}
};


//===============================Sprite================================

/**
* @brief Sprite�N���X�B�摜�`�ʂ̍ŏ��P�ʁBDrawEngine�͕`�ʃG���W�����w��B
*/
template<typename DrawEngine>
class Sprite {
public:

	typedef typename DrawEngine::ImageType ImageType;

	Sprite(ImageType img, wing::RectSize size, wing::Position position = wing::Position(0, 0) , wing::utility::StrictType<int> hit_check_rate=100, wing::utility::StrictType<bool> trance_flag=false, wing::utility::StrictType<int> type_id=0);

	/**
	*@brief �X�v���C�g�̃A�b�v�f�[�g�֐��B�K�v�Ȃ�I�[�o�[���C�h���Ďg��
	**/
	virtual void update(wing::canvas::AbstructCanvas<DrawEngine>&){}

	/**
	*@brief �X�v���C�g��Canvas�O�ɂȂ������ɌĂ΂��B�K�v�Ȃ�I�[�o�[���C�h���Ďg��
	**/
	virtual void outCanvas(){}
	/**
	*@brief Sprite��Canvas��̑���x���W���擾����
	**/
	int getPosX() const;
	/**
	*@brief Sprite��Canvas��̑���y���W���擾����
	**/
	int getPosY() const;
	/**
	*@brief Sprite��1Frame�O��Canvas��̑���x���W���擾����
	**/
	int getBeforePosX() const;
	/**
	*@brief Sprite��1Frame�O��Canvas��̑���y���W���擾����
	**/
	int getBeforePosY() const;

	/**
	*@brief ���ݐݒ肳��Ă��铖���蔻��̗̈�%��Ԃ�
	*@return �ݒ肳��Ă���l(%)
	**/
	int getHitCheckRate() const;
	/**
	*@brief ���ݐݒ肳��Ă��铧�߃��[�h���擾����
	**/
	bool getTranceFlag() const{return TranceFlag;}
	/**
	*@brief �������Ă��邩�ǂ������擾����
	**/
	bool isAlive() const;
	/**
	*@brief �ݒ肳��Ă���TypeID���擾����
	**/
	int getTypeID() const;
	/**
	*@brief Sprite��Image���擾����
	*@return �ݒ肳��Ă���C���[�W
	**/
	const ImageType& getImage() const;
	/**
	*@brief Sprite�̉������擾����
	**/
	int getWidth() const;
	/**
	*@brief Sprite�̏c�����擾����
	**/
	int getHeight() const;
	/**
	*@brief Sprite�̔��a���擾����
	*@return Sprite�Ɏ��܂�ő�̉~�̔��a
	**/
	int getRadiusSquare() const;
	
	/**
	*@brief Sprite�̐����t���O��؂�
	**/
	void kill();

	/**
	*@brief �C�x���g���X�i�[�ǉ��B�K�v�Ȃ�I�[�o�[���C�h���Ďg��
	**/
	virtual void addEventListener(const char*, std::function<void()>){}
	/**
	*@brief �C�x���g���X�i�[�폜�B�K�v�Ȃ�I�[�o�[���C�h���Ďg��
	**/
	virtual void removeEventListener(const char*){}
	/**
	*@brief �C�x���g�N���B�K�v�Ȃ�I�[�o�[���C�h���Ďg��
	**/
	virtual void listenEvent(const char*){}

	/**
	*@brief �f�X�g���N�^
	**/
	virtual ~Sprite(){}

protected:
	//�Z�b�^�[�n�͌p����ł̂ݎg����

	/**
	*@brief �����蔻��̗̈�%��ݒ肷��
	*@param hit_check_rate �X�v���C�g�ɑ΂��铖���蔻��̈��%
	**/
	void setHitCheckRate(int hit_check_rate);
	/**
	*@brief �X�v���C�g��Canvas��̑��΍��W��ݒ肷��
	*@param x �ݒ肷��x���W
	*@param y �ݒ肷��y���W
	**/
	void setLocation(int x,int y);
	/**
	*@brief �X�v���C�g�̍��W���w��ʂ����ړ�������
	@param dx x�����̈ړ���
	@param dy y�����̈ړ���
	**/
	void move(int dx,int dy);
	/**
	*@brief �摜�̃t���[��ID��ݒ�
	@param frame �t���[��ID
	**/
	void setFrame(int frame){
		image->setFrame(frame);
	}


private:
	
	//�R�s�[�E����̋֎~
	Sprite(const Sprite<DrawEngine>&);
	Sprite& operator=(Sprite<DrawEngine>&);


#pragma region PrivateMember

	ImageType image;
	const int TypeID;
	int PosX;
	int PosY;
	int BeforePosX;
	int BeforePosY;
	int Width;
	int Height;
	const bool TranceFlag;
	bool AliveFlag;
	const int HitCheckRate;
#pragma endregion

};


/**
*@brief DxLib���g���ꍇ��Sprite��Typedef
*/
typedef Sprite<wing::image::DrawEngine> DxSprite;




template<typename Decotatee>
class ImplEvent : public Decotatee{
public:

	//�R���X�g���N�^�𒊏ۉ�������...
	ImplEvent(typename Decotatee::ImageType img, wing::RectSize size, wing::Position position = wing::Position(0, 0) , int hit_check_rate=100, bool trance_flag=false,int type_id=0):
	   Decotatee( img, size, position , hit_check_rate, trance_flag, type_id){
		DefinedEventListener = std::unordered_map<const char*,std::function<void()>,std::hash<const char*>,std::function<bool(const char*, const char*)> >
	  (10,std::hash<const char*>(),
	  [](const char* lhs,const char* rhs){return (strcmp(lhs, rhs) == 0)? true : false;});
	  
	  }


	/**
	*@brief �C�x���g���X�i�[�ǉ��B
	*@param EventName �ǉ�����C�x���g��
	*@param EventListener �쓮����t�@���N�V����
	**/
	void addEventListener(const char* EventName, std::function<void()> EventListener) override {DefinedEventListener[EventName]=EventListener;}
	/**
	*@brief �C�x���g���X�i�[�폜�B
	*@param EventName �폜����C�x���g��
	**/
	void removeEventListener(const char* EventName) override {DefinedEventListener.erase(EventName);}
	/**
	*@brief �C�x���g�N���B
	*@param EventName �N������C�x���g
	**/
	void listenEvent(const char* EventName) override {if (DefinedEventListener.count(EventName)!=0) DefinedEventListener.at(EventName)();}
private:

	std::unordered_map<
		const char*,
		std::function<void()>,
		std::hash<const char*>,
		std::function<bool(const char*, const char*)>
	> DefinedEventListener;

}; 


/**
*@brief Sprite�ɃC�x���g�����@�\�������������́B
*/
template<class Engine>
class ImplEventSprite : public wing::utility::decorate<Sprite<Engine>,ImplEvent>{};

/**
*@brief DxLib���g���ꍇ��ImplEventSprite��Typedef
*/
typedef ImplEventSprite<wing::image::DrawEngine> DxImplEventSprite;



}}


//==========================����===========================


namespace wing{
namespace sprite{

template<class A, class B>
inline bool checkRectHit(const A& obj1, const B& obj2){

	if (&obj1==&obj2) return false;


	auto WidthOffset1 = (obj1.getWidth() * obj1.getHitCheckRate() ) / 100;
	auto PosXOffset1 = (obj1.getWidth() - WidthOffset1 )/2;
	auto HeightOffset1 = (obj1.getHeight() * obj1.getHitCheckRate() ) / 100;
	auto PosYOffset1 = (obj1.getHeight() - HeightOffset1 )/2;

	auto WidthOffset2 = (obj2.getWidth() * obj2.getHitCheckRate() ) / 100;
	auto PosXOffset2 = (obj2.getWidth() - WidthOffset2 )/2;
	auto HeightOffset2 = (obj2.getHeight() * obj2.getHitCheckRate() ) / 100;
	auto PosYOffset2 = (obj2.getHeight() - HeightOffset2 )/2;

	auto XStart1 = obj1.getPosX() + PosXOffset1;
	auto XEnd1 = XStart1 + WidthOffset1;
	auto YStart1 = obj1.getPosY() + PosYOffset1;
	auto YEnd1 = YStart1 + WidthOffset1;

	auto XStart2 = obj2.getPosX() + PosXOffset2;
	auto XEnd2 = XStart2 + WidthOffset2;
	auto YStart2 = obj2.getPosY() + PosYOffset2;
	auto YEnd2 = YStart2 + WidthOffset2;

	return ( XStart1 < XEnd2 ) && ( XEnd1 > XStart2 ) ? 
	( YStart1 < YEnd2 ) && ( YEnd1 > YStart2 ) : false;
}

template<class A, class B>
inline bool checkCircleHit(const A& obj1, const B& obj2){
	
	if (&obj1==&obj2) return false;
	
	auto X1 = obj1.getPosX() + obj1.getWidth()/2;
	auto X2 = obj2.getPosX() + obj2.getWidth()/2;
	auto Y1 = obj1.getPosY() + obj1.getHeight()/2;
	auto Y2 = obj2.getPosY() + obj2.getHeight()/2;

	auto R1 = (obj1.getRadiusSquare()* obj1.getHitCheckRate()) / 100;
	auto R2 = (obj1.getRadiusSquare()* obj2.getHitCheckRate()) / 100;


	return (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2) <= (R1 + R2) * (R1 + R2);

}

template<class A, class B>
inline bool checkAccuracyCircleHit(const A& obj1, const B& obj2){
	
	if (&obj1==&obj2) return false;

	//if (checkCircleHit(obj1,obj2)){
	//	return true;
	//}

	//���S���W
	auto X1 = obj1.getPosX() + obj1.getWidth()/2;
	auto Y1 = obj1.getPosY()  + obj1.getHeight()/2;

	auto X2 = obj2.getPosX() + obj2.getWidth()/2;
	auto Y2 =  obj2.getPosY() + obj2.getHeight()/2;

	//�����蔻��p�̔��a
	auto R1 = (obj1.getRadiusSquare()* obj1.getHitCheckRate()) / 100;
	auto R2 = (obj1.getRadiusSquare()* obj2.getHitCheckRate()) / 100;

	auto Vx=obj1.getPosX()-obj1.getBeforePosX();
	auto Vy=obj1.getPosY()-obj1.getBeforePosY();
	auto Ux=obj2.getPosX()-obj2.getBeforePosX();
	auto Uy=obj2.getPosY()-obj2.getBeforePosY();

	auto vx = Vx-Ux;
	auto vy = Vy-Uy;
	auto X = X1- X2;
	auto Y = Y1- Y2;
	auto R = R1 + R2;



	auto a = vx*vx+vy*vy;
	auto b = vx*X+vy*Y;
	auto c = X*X+Y*Y;

	if (b >= 0){
		return (c <= R*R);
	}
	if (b <= -2*a){
		return a+ b +c <= R*R;
	}

	return b*b>=4*a*(R*R+1);

}

template<class RemovePolicy,class CanvasClass,class Iter>
inline Iter refreshSprite(CanvasClass& Canvas, Iter begin, Iter end){


	//�L�����o�X�O�ɏo�����ǂ�������
	
	std::for_each(begin, end,
		[&](decltype(*begin)& obj){
			if ( obj->getPosX() > Canvas.getWidth() ) obj->outCanvas();
			if ( obj->getPosX() + obj->getWidth() < 0 ) obj->outCanvas();
			if ( obj->getPosY() > Canvas.getHeight() ) obj->outCanvas();
			if ( obj->getPosY() + obj->getHeight() < 0 ) obj->outCanvas();
		}
	);
	
	//���񂾃X�v���C�g�̊J��
	
	auto NewEndIter = RemovePolicy::remove(begin, end,
		[](const decltype(*begin)& obj){return obj->isAlive () == false;}
	);
	

	//Sprite��update
	std::for_each(begin, NewEndIter,
		[&](decltype(*begin)& obj){
			obj->update(Canvas);
		}
	);

	return NewEndIter;
}

//==========================Sprite����================


template<typename DrawEngine>
inline Sprite<DrawEngine>::	Sprite(ImageType img, wing::RectSize size, wing::Position position, wing::utility::StrictType<int> hit_check_rate, wing::utility::StrictType<bool> trance_flag, wing::utility::StrictType<int> type_id):
	  PosX(position.getX()),
	  PosY(position.getY()),
	  BeforePosX(position.getX()),
	  BeforePosY(position.getY()),
	  Width(size.getWidth()),
	  Height(size.getHeight()),
	  TranceFlag(trance_flag),
	  image(img),
	  HitCheckRate(hit_check_rate),
	  AliveFlag(true),
	  TypeID(type_id)
	  {}




template<typename DrawEngine>
inline void Sprite<DrawEngine>::setHitCheckRate(int hit_check_rate){
	HitCheckRate = hit_check_rate;
}

	
template<typename DrawEngine>
inline void Sprite<DrawEngine>::setLocation(int x,int y){
	BeforePosX = PosX;
	BeforePosY = PosY;
	PosX = x;
	PosY = y;
}

template<typename DrawEngine>
inline void Sprite<DrawEngine>::kill(){
	AliveFlag=false;
}

template<typename DrawEngine>
inline void Sprite<DrawEngine>::move(int dx,int dy){
	BeforePosX=PosX;
	BeforePosY=PosY;
	PosX+=dx;
	PosY+=dy;
}


template<typename DrawEngine>
inline int Sprite<DrawEngine>::getPosX() const {return PosX;}

template<typename DrawEngine>
inline int Sprite<DrawEngine>::getPosY() const {return PosY;}

template<typename DrawEngine>
inline int Sprite<DrawEngine>::getBeforePosX() const {return BeforePosX;}

template<typename DrawEngine>
inline int Sprite<DrawEngine>::getBeforePosY() const {return BeforePosY;}


template<typename DrawEngine>
inline int Sprite<DrawEngine>::getWidth() const {return Width;}

template<typename DrawEngine>
inline int Sprite<DrawEngine>::getHeight() const {return Height;}

template<typename DrawEngine>
inline int Sprite<DrawEngine>::getTypeID() const {return TypeID;}


template<typename DrawEngine>
inline int Sprite<DrawEngine>::getHitCheckRate() const{return HitCheckRate;}



template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getRadiusSquare() const {return Width > Height ? Height/2 : Width/2;}

template<typename DrawEngine>
bool Sprite<DrawEngine>::isAlive() const{return AliveFlag;}

template<typename DrawEngine>
const typename Sprite<DrawEngine>::ImageType& Sprite<DrawEngine>::getImage() const{return image;}


}}


