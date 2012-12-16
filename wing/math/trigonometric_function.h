#pragma once

#pragma comment(lib,"trigonometric_function.lib")

namespace wing{
namespace math{


/**
*@brief �ʓx�@���烉�W�A���ɕϊ�
*@param theta �ϊ��O�p�x(�x)
*@return �ϊ���p�x(���W�A��)
**/
double deg2rad(double theta);
/**
*@brief ���W�A������ʓx�@�ɕϊ�
*@param theta �ϊ��O�p�x(���W�A��)
*@return �ϊ���p�x(�x)
**/
double rad2deg(double theta);

/**
*@brief �ʓx�@�ɂ��sin
*@param theta �p�x(�x)
*@return sin�l
**/
double degsin(double theta);
/**
*@brief �ʓx�@�ɂ��sin�Bdouble ver��荂��
*@param theta �p�x(�x)
*@return sin�l
**/
double degsin(int theta);

/**
*@brief �ʓx�@�ɂ��cos
*@param theta �p�x(�x)
*@return cos�l
**/
double degcos(double theta);
/**
*@brief �ʓx�@�ɂ��cos�Bdouble ver��荂��
*@param theta �p�x(�x)
*@return cos�l
**/
double degcos(int theta);

/**
*@brief �ʓx�@�ɂ��tan�B
*@param theta �p�x(�x)
*@return tan�l
**/
double degtan(double theta);
/**
*@brief �ʓx�@�ɂ��tan�Bdouble ver��荂��
*@param theta �p�x(�x)
*@return tan�l
**/
double degtan(int theta);



}}