/*==================================

	[light.h]
	Author : o‡ãÄ‘¾

==================================*/

#pragma once
#include "main.h"

//LightƒNƒ‰ƒX
class Light
{
private:
	static LPDIRECT3DDEVICE9 pDevice;
	static D3DXVECTOR3 vecDir;
public:
	static void Init();
};


