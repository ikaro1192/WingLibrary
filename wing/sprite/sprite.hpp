#pragma once

#include<memory>
#include<vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <type_traits>
#include <string.h>

#include<iostream>



namespace wing{
namespace sprite{


//当たり判定系の関数
//矩形の判定
template<class A, class B>
bool checkRectHit(const A& obj1, const B& obj2){
	return ( ( obj1.getX() < obj2.getX() + obj2.getWidth() ) && ( obj1.getWidth() > obj2.getX() ) &&
	( obj1.getY() < obj2.getY() + obj2.getHeight() ) && ( obj1.getHeight() > obj2.getY() ));
}

template<class A, class B>
bool checkRectHit(const std::shared_ptr<A>& obj1, const std::shared_ptr<B>& obj2);

//円判定
template<class A, class B>
bool checkCircleHit(const A& obj1, const B& obj2);

template<class A, class B>
bool checkCircleHit(const std::shared_ptr<A>& obj1, const std::shared_ptr<B>& obj2);



template<typename DrawEngine>
class Sprite : public DrawEngine{
public:

	typedef typename DrawEngine::ImageType ImageType;

	Sprite(int width, int height,ImageType img, int x=0 , int y=0 , int hit_check_rate=100, bool trance_flag=false);

	
	void chatchEvent(const char* EventName);
	int getX() const;
	int getY() const;

	void draw(){DrawEngine::draw(*this);}

	const ImageType& getImage() const{return image;}
	int getWidth() const;
	int getHeight() const;
	int getRadiusSquare() const;
	
	virtual ~Sprite(){}

protected:
	//セッター系は継承先でのみ使える
	void setHitCheckRate(int HitCheckRate);
	void setLocation(int x,int y);
	void move(int dx,int dy);
	void addEventListener(const char* EventName, std::function<void()> EventListener);



#pragma region PrivateMember
private:
	ImageType image;
	int PosX;
	int PosY;
	int Width;
	int Height;
	bool TranceFlag;
	int HitCheckRate;
	std::unordered_map<
		const char*,
		std::function<void()>,
		std::hash<const char*>,
		std::function<bool(const char*, const char*)>
	> DefinedEventListener;
#pragma endregion




};


}}


//==========================method定義================


namespace wing{
namespace sprite{

template<typename DrawEngine>
inline Sprite<DrawEngine>::Sprite(int width, int height, typename DrawEngine::ImageType img, int x=0 , int y=0 , int hit_check_rate=100, bool trance_flag=false):
	  PosX(x),
	  PosY(y),
	  Width(width),
	  Height(height),
	  TranceFlag(trance_flag),
	  image(img),
	  HitCheckRate(hit_check_rate)
	  {
		//なぜかVS2010では初期化子リストでできないのでこうしている
		DefinedEventListener = std::unordered_map<const char*,std::function<void()>,std::hash<const char*>,std::function<bool(const char*, const char*)> >
		  (10,std::hash<const char*>(),
		  [](const char* lhs,const char* rhs){return (strcmp(lhs, rhs) == 0)? true : false;});
	  }




template<typename DrawEngine>
inline void Sprite<DrawEngine>::setHitCheckRate(int HitCheckRate){this->HitCheckRate = HitCheckRate;}

	
template<typename DrawEngine>
inline void Sprite<DrawEngine>::setLocation(int x,int y){PosX=x;PosY=y;}

template<typename DrawEngine>
inline void Sprite<DrawEngine>::move(int dx,int dy){PosX+=dx;PosY+=dy;}

template<typename DrawEngine>
inline void Sprite<DrawEngine>::addEventListener(const char* EventName, std::function<void()> EventListener){DefinedEventListener[EventName]=EventListener;}

template<typename DrawEngine>
inline void Sprite<DrawEngine>::chatchEvent(const char* EventName){DefinedEventListener.at(EventName)();}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getX() const {return PosX;}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getY() const {return PosY;}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getWidth() const {return Width;}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getHeight() const {return Height;}


template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getRadiusSquare() const {return Width > Height ? Height/2 : Width/2;}

}}