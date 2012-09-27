#pragma once

#include <vector>
#include "wing\canvas\canvas.hpp"
#include "wing\sprite\sprite.hpp"
#include "DxLib.h"
#include "flyweight_load.h"
#include "wing\common.hpp"

namespace wing{

/**
*@brief 画像関係の処理をまとめたもの
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
*@brief Imageを読み込む。
*@param filename ファイル名
*/
std::shared_ptr<wing::image::Image> loadImage(const char* filename){
	auto tmp = turara_soft::function::FlyweightGraph::Load(filename);	
	return std::shared_ptr<wing::image::Image>(new wing::image::Image(tmp));
}

/**
*@brief Imageをフレームに分けて読み込む。
*@param FileName_ ファイル名
*@param AllNum_ 画像の分割総数
*@param XNum_ 画像の横向きに対する分割数
*@param YNum_ 画像の縦に対する分割数
*@param ImageSize 画像の大きさ	
*/
std::shared_ptr<wing::image::Image> loadImage(const std::string& FileName_, int AllNum_ ,int XNum_ , int YNum_ ,wing::RectSize ImageSize){
	std::vector<int> tmp(AllNum_);
	turara_soft::function::FlyweightDivGraph::Load(FileName_,AllNum_,XNum_,YNum_,ImageSize.getWidth(),ImageSize.getHeight(),&tmp[0]);

	return std::shared_ptr<wing::image::Image>( new wing::image::Image(tmp.begin(),tmp.end()));
}


}}
