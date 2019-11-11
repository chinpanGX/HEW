#pragma once

#include "main.h"

//LightƒNƒ‰ƒX
class Light
{
private:
	LPDIRECT3DDEVICE9 pDevice;
	D3DXVECTOR3 vecDir;
public:
	static void Init();
	static void Uninit();
	static void Update();
};


