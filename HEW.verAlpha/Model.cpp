/*==========================================================

	[Model.cpp]
	Author : 出合翔太

===========================================================*/


#include <map>
#include "main.h"
#include "XFile.h"
#include "Model.h"


std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;
LPDIRECT3DDEVICE9 Model::g_pD3DDevice;
std::map<std::string, XFile *>g_pXFileList;	// 読み込んだXFileのリスト

//	アンロード処理
void Model::Unload()
{
	DEVICE_RELEASE(g_pD3DDevice);	//	デバイスの解放
}

//	モデルの描画処理
void Model::Draw()
{
	g_pD3DDevice = GetD3DDevice();
	// ワールド座標行列作成
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