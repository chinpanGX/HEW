/*============================================

	[Character.cpp]
	Author :　出合翔太

=============================================*/

#include "main.h"
#include "Model.h"
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
	// ワールド座標行列
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, Position.x, Position.y, Position.z);
	world_matrix *= scale_matrix * trans_matrix;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);                   

	if (pModel != NULL)
	{
		pModel->Draw();
	}
}

