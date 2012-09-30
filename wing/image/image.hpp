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


/**
@brief 描画の際のブレンドモードをセットするマニピュレータ(DXLibのSetDrawBlendMode互換)
*/
class DrawBlendMode{
public:
	/**
	@brief マニピュレータ本体
	@param blend_mode 描画ブレンドモードを指定する引数
	@param pal 描画ブレンドモードのパラメータ
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
@brief 描画輝度をセットするマニピュレータ(DXLibのSetDrawBright互換)
*/
class DrawBright{
public:

	/**
	*@brief マニピュレータ本体
	*@return RedBright 赤の描画輝度
	*@return GreenBright 緑の描画輝度
	*@return BlueBright 青の描画輝度
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
*@brief 文字列等の描写基点指定
*/
class Position{

public:
	/**
	*@brief マニピュレータ本体
	*@param x 描写基点となるx座標
	*@param y 描写基点となるy座標
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
*@brief 描写情報をクリアする
*/
class flash{};

/**
*@brief 指定のフォントデータで文字列を描画するモードに移行
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
*@brief 文字列を描画する際の色を指定
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
*@brief Imageを読み込む。
*@param filename ファイル名
*@return DrawEngineで扱えるImage
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
*@return DrawEngineで扱えるImage
*/
std::shared_ptr<wing::image::Image> loadImage(const std::string& FileName_, int AllNum_ ,int XNum_ , int YNum_ ,wing::RectSize ImageSize){
	std::vector<int> tmp(AllNum_);
	turara_soft::function::FlyweightDivGraph::Load(FileName_,AllNum_,XNum_,YNum_,ImageSize.getWidth(),ImageSize.getHeight(),&tmp[0]);

	return std::shared_ptr<wing::image::Image>( new wing::image::Image(tmp.begin(),tmp.end()));
}


}}
