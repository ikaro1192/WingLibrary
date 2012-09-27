#pragma once

#include <vector>
#include "wing\canvas\canvas.hpp"
#include "wing\sprite\sprite.hpp"
#include "DxLib.h"
#include "flyweight_load.h"
#include "wing\common.hpp"

namespace wing{

/**
*@brief �摜�֌W�̏������܂Ƃ߂�����
**/
namespace image{

class Image{
private:
	typedef int ImageData;

public:

	explicit Image(ImageData image):NowFrame(0){ImageList.push_back(image);}
	
	template<typename Iterator>
	Image(Iterator begin, Iterator end):NowFrame(0){
	
		for(auto iter = begin; iter!=end; ++iter){
			ImageList.push_back(*iter);
		}

	}

	const ImageData getImage() const{return ImageList[NowFrame];}
	const ImageData getImage(int FrameID) const{return ImageList[FrameID];}
	void setFrame(int frame){NowFrame = frame; }

#pragma region PrivateMember
private:
	int NowFrame;
	std::vector<ImageData> ImageList;
#pragma endregion
};

class DrawEngine{
public:
	typedef std::shared_ptr<Image> ImageType;

protected:

virtual ~DrawEngine(){}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas, const wing::sprite::Sprite<DrawEngine>& sprite){
	DrawGraph(canvas.getPosX() + sprite.getPosX(), canvas.getPosY() + sprite.getPosX(), (sprite.getImage()->getImage()), sprite.getTranceFlag());
}

private:

};


/**
*@brief Image��ǂݍ��ށB
*@param filename �t�@�C����
*/
std::shared_ptr<wing::image::Image> loadImage(const char* filename){
	auto tmp = turara_soft::function::FlyweightGraph::Load(filename);	
	return std::shared_ptr<wing::image::Image>(new wing::image::Image(tmp));
}

/**
*@brief Image���t���[���ɕ����ēǂݍ��ށB
*@param FileName_ �t�@�C����
*@param AllNum_ �摜�̕�������
*@param XNum_ �摜�̉������ɑ΂��镪����
*@param YNum_ �摜�̏c�ɑ΂��镪����
*@param ImageSize �摜�̑傫��	
*/
std::shared_ptr<wing::image::Image> loadImage(const std::string& FileName_, int AllNum_ ,int XNum_ , int YNum_ ,wing::RectSize ImageSize){
	std::vector<int> tmp(AllNum_);
	turara_soft::function::FlyweightDivGraph::Load(FileName_,AllNum_,XNum_,YNum_,ImageSize.getWidth(),ImageSize.getHeight(),&tmp[0]);

	return std::shared_ptr<wing::image::Image>( new wing::image::Image(tmp.begin(),tmp.end()));
}


}}
