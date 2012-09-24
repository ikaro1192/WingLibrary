#pragma once

namespace wing{

//�V���^�b�N�X��K�v�����A�Z�}���e�B�N�X��Null�̂Ƃ��ɖ����I�Ɏg���B
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