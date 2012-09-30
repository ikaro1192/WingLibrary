#pragma once

#include <vector>
#include <algorithm>
#include "wing\canvas\canvas.hpp"
#include "wing\sprite\sprite.hpp"
#include "DxLib.h"
#include "flyweight_load.h"
#include "wing\common.hpp"
#include <string>
#include <sstream>


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


/**
@brief �`��̍ۂ̃u�����h���[�h���Z�b�g����}�j�s�����[�^(DXLib��SetDrawBlendMode�݊�)
*/
class DrawBlendMode{
public:
	/**
	@brief �}�j�s�����[�^�{��
	@param blend_mode �`��u�����h���[�h���w�肷�����
	@param pal �`��u�����h���[�h�̃p�����[�^
	*/
	DrawBlendMode(int blend_mode, int pal):
		BlendMode(blend_mode),
		Pal(pal){}
	
	int getBlendMode() const {return BlendMode;}
	int getPal() const {return Pal;}

private:
const int BlendMode;
const int Pal;
};


/**
@brief �`��P�x���Z�b�g����}�j�s�����[�^(DXLib��SetDrawBright�݊�)
*/
class DrawBright{
public:

	/**
	*@brief �}�j�s�����[�^�{��
	*@return RedBright �Ԃ̕`��P�x
	*@return GreenBright �΂̕`��P�x
	*@return BlueBright �̕`��P�x
	*/
	DrawBright(int RedBright, int GreenBright , int BlueBright):
		R(RedBright),
		G(GreenBright),
		B(BlueBright){}

		int getR() const {return R;}
		int getG() const {return G;}
		int getB() const {return B;}

private:
	DrawBright(DrawBright&);
	DrawBright& operator=(DrawBright&);

	const int R;
	const int G;
	const int B;

};


/**
*@brief �����񓙂̕`�ʊ�_�w��
*/
class Position{

public:
	/**
	*@brief �}�j�s�����[�^�{��
	*@param x �`�ʊ�_�ƂȂ�x���W
	*@param y �`�ʊ�_�ƂȂ�y���W
	*/
	Position(int x,int y):
		X(x),
		Y(y)
		{}
	
	int getX() const{return X;}
	int getY() const{return Y;}

	Position(const Position& obj):
		X(obj.X),
		Y(obj.Y){}

	Position(const Position&& obj):
		X(obj.X),
		Y(obj.Y){}

private:
	Position& operator=(const Position& obj);


	const int X;
	const int Y;
	
};

/**
*@brief �`�ʏ����N���A����
*/
class flash{};

/**
*@brief �w��̃t�H���g�f�[�^�ŕ������`�悷�郂�[�h�Ɉڍs
*/
class FontDraw{
public:
	FontDraw(int font_handle):
	  FontHandle(font_handle){}

	int getFontHandle()const{return FontHandle;}

private:
	const int FontHandle;

};

/**
*@brief �������`�悷��ۂ̐F���w��
*/
class DrawStringColor{
public:
	DrawStringColor(int R, int G, int B):
	Color(GetColor(R,G,B))
	{}

	int getColor() const{return Color;}

private:
	const int Color;

};


class DrawEngine{
public:
	typedef std::shared_ptr<Image> ImageType;

protected:
	
	DrawEngine():
		PosX(0),
		PosY(0),
		HandleDrawMode(false),
		Color(GetColor(0,0,0))
	{}

virtual ~DrawEngine(){}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas, const wing::sprite::Sprite<DrawEngine>& sprite){
	DrawRectGraph(canvas.getPosX() + sprite.getPosX() + std::max<int>(-sprite.getPosX(), 0) , canvas.getPosY() + sprite.getPosY() + std::max<int>(-sprite.getPosY(), 0) , std::max<int>(-sprite.getPosX(), 0), std::max<int>(-sprite.getPosY(), 0), std::min<int>(canvas.getWidth() - sprite.getPosX() , sprite.getWidth()), std::min<int>(canvas.getHeight() - sprite.getPosY(), sprite.getHeight()),(sprite.getImage()->getImage()), sprite.getTranceFlag(), false);
}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas, const DrawBright& bright){
	SetDrawBright(bright.getR(), bright.getG(), bright.getB());
}


void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas, const wing::image::DrawBlendMode& DrawBlendMode){
	SetDrawBlendMode(DrawBlendMode.getBlendMode(), DrawBlendMode.getPal());
}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas, const wing::image::Position& DrawPosition){
	PosX=DrawPosition.getX();
	PosY=DrawPosition.getY();
}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas, const wing::Position& DrawPosition){
	PosX=DrawPosition.getX();
	PosY=DrawPosition.getY();
}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas,const wing::image::DrawStringColor& color){
	Color = color.getColor();
}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas,const wing::image::FontDraw& FontDraw){
	FontHandle = FontDraw.getFontHandle();
	HandleDrawMode = true;
}




void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas,const char* str){

	if (HandleDrawMode){
		DrawStringToHandle(canvas.getPosX() + PosX, canvas.getPosY() + PosY, str, Color,FontHandle);
		PosX+= GetDrawStringWidthToHandle(str, std::strlen(str),FontHandle);
	}else{
		DrawString(canvas.getPosX() + PosX, canvas.getPosY() + PosY, str, Color);
		PosX+= GetDrawStringWidth(str, std::strlen(str));
	}
}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas,const std::string& str){
	draw(canvas,str.c_str());
}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas,const flash&){
	PosX = 0;
	PosY = 0;
	HandleDrawMode =false;
}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas, int num){
	std::ostringstream os;
	os << num;
	draw(canvas,os.str().c_str());
}

void draw(const wing::canvas::AbstructCanvas<DrawEngine>& canvas, double num){
	std::ostringstream os;
	os << num;
	draw(canvas,os.str().c_str());
}


private:
	int PosX;
	int PosY;
	int Color;
	int FontHandle;
	bool HandleDrawMode;


};


/**
*@brief Image��ǂݍ��ށB
*@param filename �t�@�C����
*@return DrawEngine�ň�����Image
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
*@return DrawEngine�ň�����Image
*/
std::shared_ptr<wing::image::Image> loadImage(const std::string& FileName_, int AllNum_ ,int XNum_ , int YNum_ ,wing::RectSize ImageSize){
	std::vector<int> tmp(AllNum_);
	turara_soft::function::FlyweightDivGraph::Load(FileName_,AllNum_,XNum_,YNum_,ImageSize.getWidth(),ImageSize.getHeight(),&tmp[0]);

	return std::shared_ptr<wing::image::Image>( new wing::image::Image(tmp.begin(),tmp.end()));
}


}}
