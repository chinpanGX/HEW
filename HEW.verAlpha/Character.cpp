/*============================================

	[Character.cpp]
	Author :　出合翔太

=============================================*/

#include "main.h"
#include "Model.h"
#include "Drawer.h"
#include "Character.h"

//	フローバル変数
LPDIRECT3DDEVICE9 Character::g_pD3DDevice;	//	デバイス


void Character::Init()
{
	//	デバイスの取得
	g_pD3DDevice = GetD3DDevice();

}

void Character::Uninit()
{
	DEVICE_RELEASE(g_pD3DDevice);
}

void Character::Update()
{
}

void Character::Draw()
{

}

