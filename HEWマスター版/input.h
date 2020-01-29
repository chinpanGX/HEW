/*==================================
	
	[input.h]
	Author : 出合翔太

==================================*/

#pragma once

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)	//	DirectInputのバージョン
#include <dinput.h>

//Inputクラス
class Input
{
protected:
	static LPDIRECTINPUT8	m_pInput;
public:
	static bool Init(HINSTANCE hInstance);
	static void Uninit();
};

