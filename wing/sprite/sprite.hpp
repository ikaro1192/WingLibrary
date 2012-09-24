#pragma once

#include<memory>
#include<vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <type_traits>
#include <string.h>

#include<iostream>

#include "../common.hpp"


namespace wing{

namespace sprite{


//当たり判定系の関数
//矩形の判定
template<class A, class B>
bool checkRectHit(const A& obj1, const B& obj2);

//円判定
template<class A, class B>
inline bool checkCircleHit(const A& obj1, const B& obj2);


//===============================Sprite================================


template<typename DrawEngine>
class Sprite : public DrawEngine{
public:

	typedef typename DrawEngine::ImageType ImageType;

	Sprite(int width, int height,ImageType img,wing::Position position , int hit_check_rate=100, bool trance_flag=false);

	//アップデート関数(必要ならオーバーライドして使う)
	virtual void update(){}
	
	int getX() const;
	int getY() const;
	int getHitCheckRate() const;
	bool isAlive() const;
	const ImageType& getImage() const;
	int getWidth() const;
	int getHeight() const;
	int getRadiusSquare() const;

	void kill();


	virtual ~Sprite(){}

protected:
	//セッター系は継承先でのみ使える
	void setHitCheckRate(int hit_check_rate);
	void setLocation(int x,int y);
	void move(int dx,int dy);

private:

	
	//コピー・代入の禁止
	Sprite(const Sprite<DrawEngine>&);
	Sprite& operator=(Sprite<DrawEngine>&);


#pragma region PrivateMember

	ImageType image;
	int PosX;
	int PosY;
	int Width;
	int Height;
	bool TranceFlag;
	bool AliveFlag;
	int HitCheckRate;

#pragma endregion

};





}}


//==========================実装===========================


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

	auto XStart1 = obj1.getX() + PosXOffset1;
	auto XEnd1 = XStart1 + WidthOffset1;
	auto YStart1 = obj1.getY() + PosYOffset1;
	auto YEnd1 = YStart1 + WidthOffset1;

	auto XStart2 = obj2.getX() + PosXOffset2;
	auto XEnd2 = XStart2 + WidthOffset2;
	auto YStart2 = obj2.getY() + PosYOffset2;
	auto YEnd2 = YStart2 + WidthOffset2;

	return ( XStart1 < XEnd2 ) && ( XEnd1 > XStart2 ) ? 
	( YStart1 < YEnd2 ) && ( YEnd1 > YStart2 ) : false;
}

template<class A, class B>
inline bool checkCircleHit(const A& obj1, const B& obj2){
	
	if (&obj1==&obj2) return false;
	
	auto X1 = obj1.getX() + obj1.getWidth()/2;
	auto X2 = obj2.getX() + obj2.getWidth()/2;
	auto Y1 =  obj1.getY() + obj1.getHeight()/2;
	auto Y2 =  obj2.getY() + obj2.getHeight()/2;

	auto R1 = (obj1.getRadiusSquare()* obj1.getHitCheckRate()) / 100;
	auto R2 = (obj1.getRadiusSquare()* obj2.getHitCheckRate()) / 100;


	return (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2) <= (R1 + R2) * (R1 + R2);

}

//==========================Sprite================


template<typename DrawEngine>
inline Sprite<DrawEngine>::Sprite(int width, int height, typename DrawEngine::ImageType img, wing::Position position, int hit_check_rate=100, bool trance_flag=false):
	  PosX(position.getX()),
	  PosY(position.getY()),
	  Width(width),
	  Height(height),
	  TranceFlag(trance_flag),
	  image(img),
	  HitCheckRate(hit_check_rate),
	  AliveFlag(true)
	  {}




template<typename DrawEngine>
inline void Sprite<DrawEngine>::setHitCheckRate(int hit_check_rate){
	HitCheckRate = hit_check_rate;
}

	
template<typename DrawEngine>
inline void Sprite<DrawEngine>::setLocation(int x,int y){
	PosX=x;
	PosY=y;
}

template<typename DrawEngine>
inline void Sprite<DrawEngine>::kill(){
	AliveFlag=false;
}

template<typename DrawEngine>
inline void Sprite<DrawEngine>::move(int dx,int dy){
	PosX+=dx;
	PosY+=dy;
}


template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getX() const {return PosX;}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getY() const {return PosY;}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getWidth() const {return Width;}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getHeight() const {return Height;}


template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getHitCheckRate() const{return HitCheckRate;}



template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getRadiusSquare() const {return Width > Height ? Height/2 : Width/2;}

template<typename DrawEngine>
bool Sprite<DrawEngine>::isAlive() const{return AliveFlag;}

template<typename DrawEngine>
const typename Sprite<DrawEngine>::ImageType& Sprite<DrawEngine>::getImage() const{return image;}


}}