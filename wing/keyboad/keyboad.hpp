#pragma once

#include "DxLib.h"

namespace wing{

/**
*@brief キーボード関係
*
*/
namespace keyboad{

/**
*@brief キーボードのキーの状態
*
*/
enum State{
	Push,/*!< 押された */
	Hold,/*!< 押しつづけられている */
	Release,/*!< 離された */
	Free/*!< 押されていない */
};


/**
*@brief キーボードクラス。ファンクタとしてKeyCodeの状態を返す
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