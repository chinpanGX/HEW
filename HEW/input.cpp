/*==================================

	[input.cpp]
	Author : 出合翔太

====================================*/

#include "input.h"
#include "main.h"

//	スタティック変数
LPDIRECTINPUT8			Input::m_pInput = NULL;		//	DirectInputオブジェクト
			
//	DirectInputオブジェクト初期化
bool Input::Init(HINSTANCE hInstance)
{
	//	DirectInput8の作成
	if (m_pInput == NULL)
	{
		//	作成の失敗
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{

			return false;
		}
	}
	return true;	//正常終了
}

//DirectInputオブジェクト終了処理
void Input::Uninit()
{	
	DEVICE_RELEASE(m_pInput);
}
