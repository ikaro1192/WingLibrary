#pragma once


#include "wing/sprite/sprite.hpp"
#include<memory>
#include<vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <type_traits>
#include <string.h>

namespace wing{
namespace image{
class DrawEngine;
}}

/**
*@brief WingLibraryに属するもの
*/
namespace wing{
/**
*@brief 描写先となるCanvasに関係するもの
*/
namespace canvas{

/**
* @brief 描写先となるCanvasを表す抽象クラス。DrawEngineは描写エンジンを指定
*/
template<typename DrawEngine>
class AbstructCanvas : public DrawEngine{
public:

	/**
	* @brief 自分自身の型を表す型シノニム
	*/
	typedef AbstructCanvas<DrawEngine> ThisType;

	AbstructCanvas(wing::RectSize size, wing::Position position);

	AbstructCanvas(const AbstructCanvas<DrawEngine>& obj);
	AbstructCanvas& operator=(AbstructCanvas<DrawEngine>&);

	/**
	*@brief Canvasの表示起点の絶対x座標を取得する
	**/
	int getPosX() const;
	/**
	*@brief Canvasの表示起点の絶対y座標を取得する
	**/
	int getPosY() const;
	/**
	*@brief Canvasの横幅を取得する
	**/
	int getWidth() const;
	/**
	*@brief Canvasの縦幅を取得する
	**/
	int getHeight() const;

	/**
	*@brief キャンバスを更新する
	*/
	void refresh();

	/**
	*@brief 子供のキャンバスを追加する
	*@param CanvasName 追加する子供につける名前
	*@param child 追加する子供
	*/
	void addChild(const char* CanvasName, const std::shared_ptr<ThisType>& child);
	void addChild(std::string CanvasName, const std::shared_ptr<ThisType>& child){addChild(CanvasName.c_str(),child);}

	/**
	*@brief 管理するスプライトを追加する。
	*@param sprite 追加するスプライトのスマートポインタ
	*/
	void addSprite(const std::shared_ptr<wing::sprite::Sprite<DrawEngine> >& sprite);	


	/**
	*@brief フォーカス対象の子キャンバスを変更
	*@param target フォーカスを当てる子供の名前
	*/
	void changeFocus(const char* target);
	void changeFocus(std::string target){changeFocus(target.c_str());}

	/**
	*@brief 内部オブジェクトをクリアする。
	*/
	void clear();

	/**
	*@brief 指定したオブジェクトを描写する
	*@param obj 描写するオブジェクト or マニピュレータ
	*/
	template<class T>
	AbstructCanvas<DrawEngine>& operator<<(const T& obj){
		draw(*this,obj);
		return *this;
	}

	void listenEvent(const char* EventName);


	virtual ~AbstructCanvas(){}


protected:


	//オーバーライドして使う。
	/**
	*@brief フォーカスが入った時に呼ばれる。純粋仮想関数
	*/
	virtual void focusOn() = 0;
	/**
	*@brief フォーカスが入っているときにrefresh毎に呼ばれる。純粋仮想関数
	*/
	virtual void callFocusOn(ThisType&) = 0;
	/**
	*@brief refresh毎に常に呼ばれる。純粋仮想関数
	*/
	virtual void update(ThisType&) = 0;
	/**
	*@brief フォーカスがはずれた時に呼ばれる。純粋仮想関数
	*/
	virtual void focusOff()= 0;
	/**
	*@brief addSpriteが呼ばれた時に呼ばれる。必要ならオーバーライド。パラメータは追加されたSprite
	*/
	virtual void addSpriteCalled(const std::shared_ptr<wing::sprite::Sprite<wing::image::DrawEngine> >& ){}

	//イベント系
	void addEventListener(const char* EventName, std::function<void()> EventListener);
	void removeEventListener(const char* EventName);

	#pragma region PrivateMember
private:

	const int PosX;
	const int PosY;
	const int Width;
	const int Height;

	std::vector<std::shared_ptr<AbstructCanvas<DrawEngine> > > ChildList;
	std::vector<std::shared_ptr<wing::sprite::Sprite<DrawEngine> > > SpriteList;
	std::vector<std::shared_ptr<wing::sprite::Sprite<DrawEngine> > > TmpSpriteList;

	std::unordered_map<
		const char*,
		std::function<void()>,
		std::hash<const char*>,
		std::function<bool(const char*, const char*)>
	> DefinedEventListener;

	std::unordered_map<
		const char*,
		int,
		std::hash<const char*>,
		std::function<bool(const char*, const char*)>
	> ChildNameToID;

	std::shared_ptr<ThisType> NowTarget;


#pragma endregion

};

/**
*@brief DxLibを使う場合のAbstructCanvasのTypedef
*/
typedef AbstructCanvas<wing::image::DrawEngine> DxAbstructCanvas;



//==========================AbstructCanvas実装================
template<typename DrawEngine>
AbstructCanvas<DrawEngine>::AbstructCanvas(wing::RectSize size, wing::Position position):
	Width(size.getWidth()),
	Height(size.getHeight()),
	PosX(position.getX()),
	PosY(position.getY()),
	NowTarget(nullptr)
{
	DefinedEventListener = std::unordered_map<const char*,std::function<void()>,std::hash<const char*>,std::function<bool(const char*, const char*)> >
	  (10,std::hash<const char*>(),
	  [](const char* lhs,const char* rhs){return (strcmp(lhs, rhs) == 0)? true : false;});
	
	ChildNameToID =	std::unordered_map<const char*, int,std::hash<const char*>,std::function<bool(const char*, const char*)> >
	  (10,std::hash<const char*>(),
	  [](const char* lhs,const char* rhs){return (strcmp(lhs, rhs) == 0)? true : false;});


}


template<typename DrawEngine>
AbstructCanvas<DrawEngine>::AbstructCanvas(const AbstructCanvas<DrawEngine>& obj):
		PosX(obj.PosX),
		PosY(obj.PosY),
		Width(obj.Width),
		Height(obj.Height),
		ChildList(obj.ChildList),
		SpriteList(obj.SpriteList),
		TmpSpriteList(obj.TmpSpriteList),
		DefinedEventListener(obj.DefinedEventListener),
		ChildNameToID(obj.ChildNameToID),
		NowTarget(obj.NowTarget)
	{}



template<typename DrawEngine>
AbstructCanvas<DrawEngine>& AbstructCanvas<DrawEngine>::operator=(AbstructCanvas<DrawEngine>&){
		ChildList=obj.ChildList;
		SpriteList=obj.SpriteList;
		TmpSpriteList=obj.TmpSpriteList;
		DefinedEventListener=obj.DefinedEventListener;
		ChildNameToID=obj.ChildNameToID;
		NowTarget=obj.NowTarget;
	}



template<typename DrawEngine>
inline int AbstructCanvas<DrawEngine>::getPosX() const{
	return PosX;
}

template<typename DrawEngine>
inline int AbstructCanvas<DrawEngine>::getPosY() const{
	return PosY;
}

template<typename DrawEngine>
inline int AbstructCanvas<DrawEngine>::getWidth() const{
	return Width;
}

template<typename DrawEngine>
inline int AbstructCanvas<DrawEngine>::getHeight() const{
	return Height;
}


template<typename DrawEngine>
inline void AbstructCanvas<DrawEngine>::addSprite(const std::shared_ptr<wing::sprite::Sprite<DrawEngine> >& sprite){
	TmpSpriteList.push_back(sprite);
	addSpriteCalled(sprite);
}

template<typename DrawEngine>
inline void AbstructCanvas<DrawEngine>::addChild(const char* CanvasName, const std::shared_ptr<AbstructCanvas>& child){
	ChildList.push_back(child);
	ChildNameToID[CanvasName] = ChildList.size()-1;
}

template<typename DrawEngine>
inline void AbstructCanvas<DrawEngine>::addEventListener(const char* EventName, std::function<void()> EventListener){
	DefinedEventListener[EventName]=EventListener;
}

template<typename DrawEngine>
inline void AbstructCanvas<DrawEngine>::removeEventListener(const char* EventName){
	DefinedEventListener.erase(EventName);
}


template<typename DrawEngine>
void AbstructCanvas<DrawEngine>::changeFocus(const char* target){
	if (NowTarget.get()!=nullptr){
		NowTarget->focusOff();
	}
	NowTarget = ChildList.at(ChildNameToID.at(target));
	NowTarget->focusOn();
}

template<typename DrawEngine>
inline void AbstructCanvas<DrawEngine>::listenEvent(const char* EventName){
	if (DefinedEventListener.count(EventName)!=0) DefinedEventListener.at(EventName)();
}

template<typename DrawEngine>
void AbstructCanvas<DrawEngine>::refresh(){

	//Sprite追加をここで実行
	for(auto iter =TmpSpriteList.begin() ;iter !=TmpSpriteList.end(); ++iter ){
		SpriteList.push_back(*iter);
	}
	TmpSpriteList.clear();


	if (NowTarget.get()!=nullptr){
		NowTarget->callFocusOn(*this);
	}

	//子どもをrefresh・updateする
	for(auto iter = ChildList.begin(); iter != ChildList.end(); ++iter){
		(*iter)->refresh();
		(*iter)-> update(*this);
	}

	for(auto iter = SpriteList.begin(); iter != SpriteList.end(); ++iter){
		if ( ((*iter)->getPosX()) > (this->getWidth()) ) (*iter)->outCanvas();
		if ( ((*iter)->getPosX()) + (*iter)->getWidth() < 0 ) (*iter)->outCanvas();
		if ( ((*iter)->getPosY()) > (this->getHeight()) ) (*iter)->outCanvas();
		if ( ((*iter)->getPosY()) + (*iter)->getHeight() < 0 ) (*iter)->outCanvas();


	}

	//死んだスプライトの開放
	auto NewEndIter = std::remove_if(SpriteList.begin(),SpriteList.end(),
		[](const std::shared_ptr<wing::sprite::Sprite<DrawEngine> >& obj){return obj->isAlive () == false;}
	);
	SpriteList.erase( NewEndIter, SpriteList.end() );

	//Spriteをupdate
	for(auto iter = SpriteList.begin(); iter != SpriteList.end(); ++iter){
		(*iter)->update(*this);
	}




}

template<typename DrawEngine>
void AbstructCanvas<DrawEngine>::clear(){
	ChildList.clear();
	SpriteList.clear();
	DefinedEventListener.clear();
	ChildNameToID.clear();
	NowTarget = nullptr;
}



}}

