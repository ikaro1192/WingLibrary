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
*@brief Spriteに関係するSpriteクラスと当たり判定関数群
*/
namespace sprite{


//当たり判定系の関数
/**
*@brief 矩形同士(Spriteを想定)の当たり判定
*@param obj1 当たり判定を行うオブジェクト1
*@param obj2 当たり判定を行うオブジェクト2
*@return 当たっていればtrue。当たっていない、自分自身の場合false
**/
template<class A, class B>
bool checkRectHit(const A& obj1, const B& obj2);

/**
*@brief 円同士(Spriteを想定)の当たり判定
*@param obj1 当たり判定を行うオブジェクト1
*@param obj2 当たり判定を行うオブジェクト2
*@return 当たっていればtrue。当たっていない、自分自身の場合false
**/
template<class A, class B>
inline bool checkCircleHit(const A& obj1, const B& obj2);


//===============================Sprite================================

/**
* @brief Spriteクラス。画像描写の最小単位。DrawEngineは描写エンジンを指定。
*/
template<typename DrawEngine>
class Sprite {
public:

	typedef typename DrawEngine::ImageType ImageType;

	Sprite(ImageType img, wing::RectSize size, wing::Position position = wing::Position(0, 0) , int hit_check_rate=100, bool trance_flag=false,int type_id=0);

	/**
	*@brief スプライトのアップデート関数。必要ならオーバーライドして使う
	**/
	virtual void update(wing::canvas::AbstructCanvas<DrawEngine>&){}

	/**
	*@brief スプライトがCanvas外になった時に呼ばれる。必要ならオーバーライドして使う
	**/
	virtual void outCanvas(){}
	
	/**
	*@brief SpriteのCanvas上の相対x座標を取得する
	**/
	int getPosX() const;
	/**
	*@brief SpriteのCanvas上の相対y座標を取得する
	**/
	int getPosY() const;
	/**
	*@brief 現在設定されている当たり判定の領域%を返す
	*@return 設定されている値(%)
	**/
	int getHitCheckRate() const;
	/**
	*@brief 現在設定されている透過モードを取得する
	**/
	bool getTranceFlag() const{return TranceFlag;}
	/**
	*@brief 生存しているかどうかを取得する
	**/
	bool isAlive() const;
	/**
	*@brief 設定されているTypeIDを取得する
	**/
	int getTypeID() const;
	/**
	*@brief SpriteのImageを取得する
	*@return 設定されているイメージ
	**/
	const ImageType& getImage() const;
	/**
	*@brief Spriteの横幅を取得する
	**/
	int getWidth() const;
	/**
	*@brief Spriteの縦幅を取得する
	**/
	int getHeight() const;
	/**
	*@brief Spriteの半径を取得する
	*@return Spriteに収まる最大の円の半径
	**/
	int getRadiusSquare() const;
	
	/**
	*@brief Spriteの生存フラグを切る
	**/
	void kill();

	/**
	*@brief イベントリスナー追加。必要ならオーバーライドして使う
	**/
	virtual void addEventListener(const char*, std::function<void()>){}
	/**
	*@brief イベントリスナー削除。必要ならオーバーライドして使う
	**/
	virtual void removeEventListener(const char*){}
	/**
	*@brief イベント起動。必要ならオーバーライドして使う
	**/
	virtual void listenEvent(const char*){}

	/**
	*@brief デストラクタ
	**/
	virtual ~Sprite(){}

protected:
	//セッター系は継承先でのみ使える

	/**
	*@brief 当たり判定の領域%を設定する
	*@param hit_check_rate スプライトに対する当たり判定領域の%
	**/
	void setHitCheckRate(int hit_check_rate);
	/**
	*@brief スプライトのCanvas上の相対座標を設定する
	*@param x 設定するx座標
	*@param y 設定するy座標
	**/
	void setLocation(int x,int y);
	/**
	*@brief スプライトの座標を指定量だけ移動させる
	@param dx x方向の移動量
	@param dy y方向の移動量
	**/
	void move(int dx,int dy);
	/**
	*@brief 画像のフレームIDを設定
	@param frame フレームID
	**/
	void setFrame(int frame){
		image->setFrame(frame);
	}


private:
	
	//コピー・代入の禁止
	Sprite(const Sprite<DrawEngine>&);
	Sprite& operator=(Sprite<DrawEngine>&);


#pragma region PrivateMember

	ImageType image;
	const int TypeID;
	int PosX;
	int PosY;
	int Width;
	int Height;
	bool TranceFlag;
	bool AliveFlag;
	int HitCheckRate;
#pragma endregion

};


/**
*@brief DxLibを使う場合のSpriteのTypedef
*/
typedef Sprite<wing::image::DrawEngine> DxSprite;




template<typename Decotatee>
class ImplEvent : public Decotatee{
public:

	//コンストラクタを抽象化したい...
	ImplEvent(typename Decotatee::ImageType img, wing::RectSize size, wing::Position position = wing::Position(0, 0) , int hit_check_rate=100, bool trance_flag=false,int type_id=0):
	   Decotatee( img, size, position , hit_check_rate, trance_flag, type_id){
		DefinedEventListener = std::unordered_map<const char*,std::function<void()>,std::hash<const char*>,std::function<bool(const char*, const char*)> >
	  (10,std::hash<const char*>(),
	  [](const char* lhs,const char* rhs){return (strcmp(lhs, rhs) == 0)? true : false;});
	  
	  }


	/**
	*@brief イベントリスナー追加。
	*@param EventName 追加するイベント名
	*@param EventListener 駆動するファンクション
	**/
	void addEventListener(const char* EventName, std::function<void()> EventListener) override {DefinedEventListener[EventName]=EventListener;}
	/**
	*@brief イベントリスナー削除。
	*@param EventName 削除するイベント名
	**/
	void removeEventListener(const char* EventName) override {DefinedEventListener.erase(EventName);}
	/**
	*@brief イベント起動。
	*@param EventName 起動するイベント
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
*@brief Spriteにイベント処理機能をもたせたもの。
*/
template<class Engine>
class ImplEventSprite : public wing::utility::decorate<Sprite<Engine>,ImplEvent>{};

/**
*@brief DxLibを使う場合のImplEventSpriteのTypedef
*/
typedef ImplEventSprite<wing::image::DrawEngine> DxImplEventSprite;



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
	auto Y1 =  obj1.getPosY() + obj1.getHeight()/2;
	auto Y2 =  obj2.getPosY() + obj2.getHeight()/2;

	auto R1 = (obj1.getRadiusSquare()* obj1.getHitCheckRate()) / 100;
	auto R2 = (obj1.getRadiusSquare()* obj2.getHitCheckRate()) / 100;


	return (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2) <= (R1 + R2) * (R1 + R2);

}


//==========================Sprite実装================


template<typename DrawEngine>
inline Sprite<DrawEngine>::Sprite(typename DrawEngine::ImageType img, wing::RectSize size, wing::Position position, int hit_check_rate=100, bool trance_flag=false, int type_id=0):
	  PosX(position.getX()),
	  PosY(position.getY()),
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
inline	int Sprite<DrawEngine>::getPosX() const {return PosX;}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getPosY() const {return PosY;}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getWidth() const {return Width;}

template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getHeight() const {return Height;}

template<typename DrawEngine>
inline int Sprite<DrawEngine>::getTypeID() const {return TypeID;}


template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getHitCheckRate() const{return HitCheckRate;}



template<typename DrawEngine>
inline	int Sprite<DrawEngine>::getRadiusSquare() const {return Width > Height ? Height/2 : Width/2;}

template<typename DrawEngine>
bool Sprite<DrawEngine>::isAlive() const{return AliveFlag;}

template<typename DrawEngine>
const typename Sprite<DrawEngine>::ImageType& Sprite<DrawEngine>::getImage() const{return image;}


}}


