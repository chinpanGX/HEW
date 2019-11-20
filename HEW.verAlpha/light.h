/*==================================

	[light.h]
	Author : èoçá„ƒëæ

==================================*/

#pragma once
#include "main.h"

//LightÉNÉâÉX
class Light
{
private:
	static LPDIRECT3DDEVICE9 pDevice;
	static D3DXVECTOR3 vecDir;
public:
	static void Init();
	static void Uninit();
	static void Update();
};


