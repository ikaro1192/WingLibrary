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
*@brief WingLibrary�ɑ��������
*/
namespace wing{
/**
*@brief �`�ʐ�ƂȂ�Canvas�Ɋ֌W�������
*/
namespace canvas{

/**
* @brief �`�ʐ�ƂȂ�Canvas��\�����ۃN���X�BDrawEngine�͕`�ʃG���W�����w��
*/
template<typename DrawEngine>
class AbstructCanvas : public DrawEngine{
public:

	/**
	* @brief �������g�̌^��\���^�V�m�j��
	*/
	typedef AbstructCanvas<DrawEngine> ThisType;

	AbstructCanvas(wing::RectSize size, wing::Position position);

	AbstructCanvas(const AbstructCanvas<DrawEngine>& obj);
	AbstructCanvas& operator=(AbstructCanvas<DrawEngine>&);

	/**
	*@brief Canvas�̕\���N�_�̐��x���W���擾����
	**/
	int getPosX() const;
	/**
	*@brief Canvas�̕\���N�_�̐��y���W���擾����
	**/
	int getPosY() const;
	/**
	*@brief Canvas�̉������擾����
	**/
	int getWidth() const;
	/**
	*@brief Canvas�̏c�����擾����
	**/
	int getHeight() const;

	/**
	*@brief �L�����o�X���X�V����
	*/
	void refresh();

	/**
	*@brief �q���̃L�����o�X��ǉ�����
	*@param CanvasName �ǉ�����q���ɂ��閼�O
	*@param child �ǉ�����q��
	*/
	void addChild(const char* CanvasName, const std::shared_ptr<ThisType>& child);
	void addChild(std::string CanvasName, const std::shared_ptr<ThisType>& child){addChild(CanvasName.c_str(),child);}

	/**
	*@brief �Ǘ�����X�v���C�g��ǉ�����B
	*@param sprite �ǉ�����X�v���C�g�̃X�}�[�g�|�C���^
	*/
	void addSprite(const std::shared_ptr<wing::sprite::Sprite<DrawEngine> >& sprite);	


	/**
	*@brief �t�H�[�J�X�Ώۂ̎q�L�����o�X��ύX
	*@param target �t�H�[�J�X�𓖂Ă�q���̖��O
	*/
	void changeFocus(const char* target);
	void changeFocus(std::string target){changeFocus(target.c_str());}

	/**
	*@brief �����I�u�W�F�N�g���N���A����B
	*/
	void clear();

	/**
	*@brief �w�肵���I�u�W�F�N�g��`�ʂ���
	*@param obj �`�ʂ���I�u�W�F�N�g or �}�j�s�����[�^
	*/
	template<class T>
	AbstructCanvas<DrawEngine>& operator<<(const T& obj){
		draw(*this,obj);
		return *this;
	}

	void listenEvent(const char* EventName);


	virtual ~AbstructCanvas(){}


protected:


	//�I�[�o�[���C�h���Ďg���B
	/**
	*@brief �t�H�[�J�X�����������ɌĂ΂��B�������z�֐�
	*/
	virtual void focusOn() = 0;
	/**
	*@brief �t�H�[�J�X�������Ă���Ƃ���refresh���ɌĂ΂��B�������z�֐�
	*/
	virtual void callFocusOn(ThisType&) = 0;
	/**
	*@brief refresh���ɏ�ɌĂ΂��B�������z�֐�
	*/
	virtual void update(ThisType&) = 0;
	/**
	*@brief �t�H�[�J�X���͂��ꂽ���ɌĂ΂��B�������z�֐�
	*/
	virtual void focusOff()= 0;
	/**
	*@brief addSprite���Ă΂ꂽ���ɌĂ΂��B�K�v�Ȃ�I�[�o�[���C�h�B�p�����[�^�͒ǉ����ꂽSprite
	*/
	virtual void addSpriteCalled(const std::shared_ptr<wing::sprite::Sprite<wing::image::DrawEngine> >& ){}

	//�C�x���g�n
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
*@brief DxLib���g���ꍇ��AbstructCanvas��Typedef
*/
typedef AbstructCanvas<wing::image::DrawEngine> DxAbstructCanvas;



//==========================AbstructCanvas����================
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

	//Sprite�ǉ��������Ŏ��s
	for(auto iter =TmpSpriteList.begin() ;iter !=TmpSpriteList.end(); ++iter ){
		SpriteList.push_back(*iter);
	}
	TmpSpriteList.clear();


	if (NowTarget.get()!=nullptr){
		NowTarget->callFocusOn(*this);
	}

	//�q�ǂ���refresh�Eupdate����
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

	//���񂾃X�v���C�g�̊J��
	auto NewEndIter = std::remove_if(SpriteList.begin(),SpriteList.end(),
		[](const std::shared_ptr<wing::sprite::Sprite<DrawEngine> >& obj){return obj->isAlive () == false;}
	);
	SpriteList.erase( NewEndIter, SpriteList.end() );

	//Sprite��update
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

