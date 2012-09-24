#pragma once

namespace wing{

//シンタックス上必要だが、セマンティクス上Nullのときに明示的に使う。
class NullType{};


class Position{

public:
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




}