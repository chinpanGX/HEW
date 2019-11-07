/*==============================================

	[XFile.h]
	Author : 出合翔太

===============================================*/

#pragma once
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>


// 読み込みファイル名リスト
std::string file_name_list[] =
{
	"ri.x",
};

//#	XFileクラス
/* XFileのロード、アンロードを管理するクラス */
class XFile
{
private:
	static DWORD						MeshNum;				//	メッシュ数
	static LPD3DXMESH					Mesh;					//	メッシュ
	static D3DMATERIAL9					*pMeshMaterialList;		//	メッシュマテリアル
	static LPDIRECT3DTEXTURE9			*pTextureList;			//	テクスチャリスト
	std::map<int, std::string> m_TextureNameList;				// テクスチャ名リスト
	static LPDIRECT3DDEVICE9			g_pD3Device;			//	デバイス
public:
	bool Load(std::string fliename);
	void Unload();
	void Draw();
};


