#pragma once

#include<memory>
#include<vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <type_traits>
#include <string.h>

#include "../common.hpp"
#include "../wing/sprite/sprite.hpp"


namespace wing{
namespace canvas{

template<typename DrawEngine>
class Canvas{
public:

	typedef Canvas<DrawEngine> ThisType;


	Canvas(wing::RectSize size, wing::Position position);

	int getPosX() const;
	int getPosY() const;
	int getWidth() const;
	int getHeight() const;

	void refresh();
	
	void addChild(const char* CanvasName, const std::shared_ptr<ThisType>& child);
	
	void changeFocus(const char* target);
	

	void listenEvent(const char* EventName);


	virtual ~Canvas(){}


protected:

	void addSprite(const std::shared_ptr<wing::sprite::Sprite<DrawEngine> >& sprite);	


	void addEventListener(const char* EventName, std::function<void()> EventListener);
	void removeEventListener(const char* EventName);

private:
	
	//コピー・代入禁止
	Canvas(const Canvas<DrawEngine>&);
	Canvas& operator=(Canvas<DrawEngine>&);
	
	//オーバーライドして使う。
	virtual void focusOn() = 0;
	virtual void callFocusOn(ThisType&) = 0;
	virtual void update(ThisType&) = 0;
	virtual void focusOff()= 0;
	
#pragma region PrivateMember

	const int PosX;
	const int PosY;
	const int Width;
	const int Height;

	std::vector<std::shared_ptr<Canvas<DrawEngine> > > ChildList;
	std::vector<std::shared_ptr<wing::sprite::Sprite<DrawEngine> > > SpriteList;

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



//==========================Canvas================
template<typename DrawEngine>
Canvas<DrawEngine>::Canvas(wing::RectSize size, wing::Position position):
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
inline int Canvas<DrawEngine>::getPosX() const{
	return PosX;
}

template<typename DrawEngine>
inline int Canvas<DrawEngine>::getPosY() const{
	return PosY;
}

template<typename DrawEngine>
inline int Canvas<DrawEngine>::getWidth() const{
	return Width;
}

template<typename DrawEngine>
inline int Canvas<DrawEngine>::getHeight() const{
	return Height;
}


template<typename DrawEngine>
inline void Canvas<DrawEngine>::addSprite(const std::shared_ptr<wing::sprite::Sprite<DrawEngine> >& sprite){
	SpriteList.push_back(sprite);
}

template<typename DrawEngine>
inline void Canvas<DrawEngine>::addChild(const char* CanvasName, const std::shared_ptr<Canvas>& child){
	ChildList.push_back(child);
	ChildNameToID[CanvasName] = ChildList.size()-1;
}

template<typename DrawEngine>
inline void Canvas<DrawEngine>::addEventListener(const char* EventName, std::function<void()> EventListener){
	DefinedEventListener[EventName]=EventListener;
}

template<typename DrawEngine>
inline void Canvas<DrawEngine>::removeEventListener(const char* EventName){
	DefinedEventListener.erase(EventName);
}


template<typename DrawEngine>
void Canvas<DrawEngine>::changeFocus(const char* target){
	if (NowTarget.get()!=nullptr){
		NowTarget->focusOff();
	}
	NowTarget = ChildList.at(ChildNameToID.at(target));
	NowTarget->focusOn();
}

template<typename DrawEngine>
inline void Canvas<DrawEngine>::listenEvent(const char* EventName){
	if (DefinedEventListener.count(EventName)!=0) DefinedEventListener.at(EventName)();
}

template<typename DrawEngine>
void Canvas<DrawEngine>::refresh(){

	if (NowTarget.get()!=nullptr){
		NowTarget->callFocusOn(*this);
	}

	//子どもをrefreshする
	for(auto iter = ChildList.begin(); iter != ChildList.end(); ++iter){
		(*iter)->refresh();
		(*iter)-> update(*this);
	}

	//死んだスプライトの開放
	auto NewEndIter = std::remove_if(SpriteList.begin(),SpriteList.end(),
		[](const std::shared_ptr<wing::sprite::Sprite<DrawEngine> >& obj){return obj->isAlive () == false;}
	);
	SpriteList.erase( NewEndIter, SpriteList.end() );

	//Spriteをupdate
	for(auto iter = SpriteList.begin(); iter != SpriteList.end(); ++iter){
		(*iter)->update();
	}


}


}}