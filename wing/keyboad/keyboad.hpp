#pragma once

#include "DxLib.h"

namespace wing{

/**
*@brief �L�[�{�[�h�֌W
*
*/
namespace keyboad{

/**
*@brief ���݉�����Ă���L�[�̎擾
*@return ������Ă���Ή�����Ă���L�[�R�[�h�A������Ă��Ȃ����-1
*/
int getNowPushKey(){
	char AllKey[256];
	GetHitKeyStateAll(AllKey);
	for(auto i = 0; i < 256; ++i){
		if ( AllKey[i] == 1 ) return i;
	} 
	return -1;
}

/**
*@brief �L�[�{�[�h�̃L�[�̏��
*
*/
enum State{
	Push,/*!< �����ꂽ */
	Hold,/*!< �����Â����Ă��� */
	Release,/*!< �����ꂽ */
	Free/*!< ������Ă��Ȃ� */
};


/**
*@brief �L�[�{�[�h�N���X�B�t�@���N�^�Ƃ���KeyCode�̏�Ԃ�Ԃ�
*
*/
class Keyboad{
public:

	Keyboad(int key_code):
	KeyCode(key_code),
	BeforeKeyState(0)
	{}

	State operator()(){
		
		const auto KeyState = CheckHitKey(KeyCode);
		
		if ( BeforeKeyState == 0 && KeyState == 1 ) {BeforeKeyState=KeyState; return Push;}
		if ( BeforeKeyState == 1 && KeyState == 1 ) {BeforeKeyState=KeyState; return Hold;}
		if ( BeforeKeyState == 1 && KeyState == 0 ) {BeforeKeyState=KeyState; return Release;}
		return Free;

	}

private:
	const int KeyCode;
	int BeforeKeyState;


};


}}