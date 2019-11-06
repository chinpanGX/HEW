/*==============================================

	[Model.h]
	Author : 出合翔太

===============================================*/

#pragma once
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

//#	Modelクラス
/* XFileのロード、アンロードを管理するクラス */
class Model
{
private:
	static DWORD						MeshNum;					//	メッシュ数
	static LPD3DXMESH					Mesh;						//	メッシュ
	static D3DMATERIAL9					*pMeshMaterialList;			//	メッシュマテリアル
	static LPDIRECT3DTEXTURE9			*pTextureList;				//	テクスチャリスト;
	static LPDIRECT3DDEVICE9			g_pD3Device;				//	デバイス
public:
	bool Load();
	void Unload();
	void Draw();
};

