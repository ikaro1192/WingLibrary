#include "../gtest/gtest.h"
#include "../wing/sprite/sprite.hpp"
#include <iostream>
#include <math.h>
#pragma warning( disable : 4512 )


namespace wing{


class Image{
private:
	typedef int ImageData;

public:


	explicit Image(ImageData image):ImageList(16){ImageList.push_back(image);}
	
	template<typename Iterator>
	Image(std::add_const<Iterator> begin, std::add_const<Iterator> end):ImageList(16){
	
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
	TestSprite(int width, int height,ImageType img,wing::Position position =wing::Position(0,0) , int hit_check_rate=100, bool trance_flag=false):
		wing::sprite::Sprite<wing::DefaltDrawEngine>(width, height, img, position, hit_check_rate, trance_flag)
	{



	}
private:


};


class RootCanvas : public wing::sprite::Canvas<wing::DefaltDrawEngine>{
public:
RootCanvas():
	wing::sprite::Canvas<wing::DefaltDrawEngine>(640,480,0,0){}

	void update(ThisType&){}




};



class TestCanvas : public wing::sprite::Canvas<wing::DefaltDrawEngine>{
public:
TestCanvas(int& test1):
	wing::sprite::Canvas<wing::DefaltDrawEngine>(640,480,0,0),
	Test1(test1)
	{}

void update(ThisType&){
		 Test1=3;
	  }


private:
	int& Test1;


};



TEST( Sprite_Test, KillTest ){
	wing::DefaltLoader Loader;
	auto img = Loader.load();

	TestSprite Hoge(100,100,img);

	ASSERT_EQ(Hoge.isAlive(), true );

	Hoge.kill();

	ASSERT_EQ(Hoge.isAlive(), false );


}



TEST( Sprite_Test, getRadiusSquareTest ){

	wing::DefaltLoader Loader;
	auto img = Loader.load();

	TestSprite Hoge(100,80,img);

	ASSERT_EQ(Hoge.getRadiusSquare() ,40);

	TestSprite Foo(50,80,img);
	ASSERT_EQ(Foo.getRadiusSquare() ,25);


}


TEST( Hit_Check_Test, RectHit ){

	wing::DefaltLoader Loader;
	auto img = Loader.load();

	TestSprite Hoge(100,100,img);

	TestSprite Foo(50,80,img);
	ASSERT_EQ(wing::sprite::checkRectHit(Hoge,Foo) , true);
	ASSERT_EQ(wing::sprite::checkRectHit(Foo,Hoge) , true);


	TestSprite Foo2(50,80,img,wing::Position(80,80) );
	ASSERT_EQ(wing::sprite::checkRectHit(Hoge,Foo2) , true);
	ASSERT_EQ(wing::sprite::checkRectHit(Foo2,Hoge) , true);

	
	TestSprite Foo3(50,80,img,wing::Position(100,80));
	ASSERT_EQ(wing::sprite::checkRectHit(Hoge,Foo3) , false);
	ASSERT_EQ(wing::sprite::checkRectHit(Foo3,Hoge) , false);


	TestSprite Foo4(50,80,img,wing::Position(80,120));
	ASSERT_EQ(wing::sprite::checkRectHit(Hoge,Foo3) , false);
	ASSERT_EQ(wing::sprite::checkRectHit(Foo3,Hoge) , false);

}

TEST( Hit_Check_Test, RectHitChangeRate ){
	wing::DefaltLoader Loader;
	auto img = Loader.load();

	TestSprite Hoge(100,100, img, wing::Position(0, 0), 80);
	TestSprite Foo(100,100, img, wing::Position(70, 70), 100);

	ASSERT_EQ(wing::sprite::checkRectHit(Hoge, Hoge) , false);



	ASSERT_EQ(wing::sprite::checkRectHit(Hoge, Foo) , true);
	ASSERT_EQ(wing::sprite::checkRectHit(Foo, Hoge) , true);

	TestSprite Foo1(100,100,img, wing::Position(90,70), 100);

	ASSERT_EQ(wing::sprite::checkRectHit(Hoge, Foo1) , false);
	ASSERT_EQ(wing::sprite::checkRectHit(Foo1, Hoge) , false);

	TestSprite Foo2(100,100,img, wing::Position(70,90), 100);

	ASSERT_EQ(wing::sprite::checkRectHit(Hoge, Foo2) , false);
	ASSERT_EQ(wing::sprite::checkRectHit(Foo2, Hoge) , false);

	TestSprite Foo3(5, 5, img);

	ASSERT_EQ(wing::sprite::checkRectHit(Hoge, Foo3) , false);
	ASSERT_EQ(wing::sprite::checkRectHit(Foo3, Hoge) , false);

	TestSprite Foo4(5, 5, img, wing::Position(10,10));

	ASSERT_EQ(wing::sprite::checkRectHit(Hoge, Foo4) , true);
	ASSERT_EQ(wing::sprite::checkRectHit(Foo4, Hoge) , true);


}

TEST( Hit_Check_Test, CircleHit ){
	
	wing::DefaltLoader Loader;
	auto img = Loader.load();

	{
		TestSprite Hoge(60,60,img,wing::Position(-10,20));
		TestSprite Foo(80,80,img,wing::Position(80,-10));
		ASSERT_EQ(wing::sprite::checkRectHit(Hoge, Hoge) , false);

		ASSERT_EQ(wing::sprite::checkCircleHit(Hoge, Foo) , false);
	}

	{
		TestSprite Hoge(60,60,img,wing::Position(-0,0));
		TestSprite Foo(80,80,img,wing::Position(20,0));

		ASSERT_EQ(wing::sprite::checkCircleHit(Hoge, Foo) , true);
	}

	{
		TestSprite Hoge(60,60,img,wing::Position(0,0));
		TestSprite Foo(80,80,img,wing::Position(70,0));

		ASSERT_EQ(wing::sprite::checkCircleHit(Hoge, Foo) , false);
	}

}

TEST( Canvas_Test, Init ){

	auto a = 0;

	TestCanvas Hoge(a);
	
	ASSERT_EQ(Hoge.getPosX() , 0);
	ASSERT_EQ(Hoge.getPosY() , 0);
	ASSERT_EQ(Hoge.getWidth() , 640);
	ASSERT_EQ(Hoge.getHeight() , 480);

}


TEST( Canvas_Test, Update ){

	auto a = 0;

	RootCanvas Root;

	auto Hoge = std::shared_ptr<TestCanvas>(new TestCanvas(a));

	Root.addChild(Hoge);

	ASSERT_EQ(a, 0);
	Root.refresh();

	ASSERT_EQ(a, 3);
	
	
}

TEST( Sprite_Test, SpeedTest ){
	wing::DefaltLoader Loader;
	auto img = Loader.load();

	for(int i=0;i<10000;++i){
	auto Hoge = std::shared_ptr<TestSprite>( new TestSprite(100,100,img,wing::Position(0,0),80));
	}

}