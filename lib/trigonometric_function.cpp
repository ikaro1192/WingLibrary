

#include<math.h>

namespace wing{
namespace math{


const double SinTable[1]={2.1};

static const auto PI = 3.1415926535897932384626433832795;

double deg2rad(double theta){
	return (theta*wing::math::PI)/180.0;
}
double rad2deg(double theta){
	return (theta*180)/wing::math::PI;
}


double degsin(double theta){
	return sin((theta*wing::math::PI)/180.0);
}
double degsin(int theta){
	return sin((theta*wing::math::PI)/180.0);//sin((theta*wing::math::PI)/180.0);
}

double degcos(double theta){
	return cos((theta*wing::math::PI)/180.0);
}
double degcos(int theta){
	return cos((theta*wing::math::PI)/180.0);//sin((theta*wing::math::PI)/180.0);
}

double degtan(double theta){
	return tan((theta*wing::math::PI)/180.0);
}
double degtan(int theta){
	return tan((theta*wing::math::PI)/180.0);//sin((theta*wing::math::PI)/180.0);
}




}}