/*==========================================================

	[Drawer.cpp]
	Author : 出合翔太

===========================================================*/


#include <map>
#include "Drawer.h"
#include "model.h"


std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;
LPDIRECT3DDEVICE9 g_pD3DDevice;
std::map<std::string, Model *>g_pXFileList;	// 読み込んだXFileのリスト

void Drawer::Draw(void)
{
	// ワールド座標行列作成 start
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, position.x, position.y, position.z);
	D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, scale.y);
	world_matrix *= scale_matrix * trans_matrix;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if (pmodel != NULL)
	{
		pmodel->Draw();
	}
}