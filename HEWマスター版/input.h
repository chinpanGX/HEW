/*==================================
	
	[input.h]
	Author : �o���đ�

==================================*/

#pragma once

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)	//	DirectInput�̃o�[�W����
#include <dinput.h>

//Input�N���X
class Input
{
protected:
	static LPDIRECTINPUT8	m_pInput;
public:
	static bool Init(HINSTANCE hInstance);
	static void Uninit();
};

