#include "../gtest/gtest.h"
#include "../wing/sprite/sprite.hpp"
#include <iostream>
#pragma warning( disable : 4512 )


namespace wing{


class Image{
private:
	typedef int ImageData;

public:


	explicit Image(ImageData image):ImageList(10){ImageList.push_back(image);}
	
	template<typename Iterator>
	Image(std::add_const<Iterator> begin,std::add_const<Iterator> end):ImageList(10){
		for(auto iter = begin; iter!=end; ++iter){
			ImageList.push_back(*iter);
		}
	}

	ImageData getImage(){return ImageList[NowFrame];}
	ImageData setFrame(int frame){NowFrame = frame; }

#pragma region PrivateMember
private:
	int NowFrame;
	std::vector<ImageData> ImageList;
#pragma endregion
	

	
};


class DefaltDrawEngine{
public:
	typedef std::shared_ptr<Image> ImageType;

protected:

	~DefaltDrawEngine(){}

	template<class T>
	void draw(const T& obj){
		obj.getX();
		obj.getY();
		std::cout<< *(obj.getImage()) <<std::endl;
	}

private:

};


class DefaltLoader{
public:
	typedef std::shared_ptr<Image> ImageType;

	ImageType load(){
		return std::shared_ptr<Image>(new Image(2));
	}

};

}




class TestSprite : public wing::sprite::Sprite<wing::DefaltDrawEngine>{
public:
	TestSprite(int width, int height,ImageType img, int x=0 , int y=0 , int hit_check_rate=100, bool trance_flag=false):
		wing::sprite::Sprite<wing::DefaltDrawEngine>(width, height, img, x, y, hit_check_rate, trance_flag)
	{

		sx=10;
		addEventCatcher("hoge", [this](){
			setLocation(this->sx,20);
		});
		addEventCatcher("bar", [this](){
			setLocation(30,40);
		});

	}
private:
	int sx;


};


TEST( Sprite_Test, EventCatchTest ){

	wing::DefaltLoader Loader;
	auto img = Loader.load();

	TestSprite Hoge(100,100,img);
	
	ASSERT_EQ(Hoge.getX(),0);
	ASSERT_EQ(Hoge.getY(),0);
	
	Hoge.chatchEvent("hoge");
	ASSERT_EQ(Hoge.getX(),10);
	ASSERT_EQ(Hoge.getY(),20);

	Hoge.chatchEvent("bar");
	ASSERT_EQ(Hoge.getX(),30);
	ASSERT_EQ(Hoge.getY(),40);

}

TEST( Sprite_Test, getRadiusSquareTest ){

	wing::DefaltLoader Loader;
	auto img = Loader.load();

	TestSprite Hoge(100,80,img);

	ASSERT_EQ(Hoge.getRadiusSquare() ,40);

	TestSprite Foo(50,80,img);
	ASSERT_EQ(Foo.getRadiusSquare() ,25);


}

