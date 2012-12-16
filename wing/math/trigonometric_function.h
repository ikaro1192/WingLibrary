#pragma once

#pragma comment(lib,"trigonometric_function.lib")

namespace wing{
namespace math{


/**
*@brief 弧度法からラジアンに変換
*@param theta 変換前角度(度)
*@return 変換後角度(ラジアン)
**/
double deg2rad(double theta);
/**
*@brief ラジアンから弧度法に変換
*@param theta 変換前角度(ラジアン)
*@return 変換後角度(度)
**/
double rad2deg(double theta);

/**
*@brief 弧度法によるsin
*@param theta 角度(度)
*@return sin値
**/
double degsin(double theta);
/**
*@brief 弧度法によるsin。double verより高速
*@param theta 角度(度)
*@return sin値
**/
double degsin(int theta);

/**
*@brief 弧度法によるcos
*@param theta 角度(度)
*@return cos値
**/
double degcos(double theta);
/**
*@brief 弧度法によるcos。double verより高速
*@param theta 角度(度)
*@return cos値
**/
double degcos(int theta);

/**
*@brief 弧度法によるtan。
*@param theta 角度(度)
*@return tan値
**/
double degtan(double theta);
/**
*@brief 弧度法によるtan。double verより高速
*@param theta 角度(度)
*@return tan値
**/
double degtan(int theta);



}}