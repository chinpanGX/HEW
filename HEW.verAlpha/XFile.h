/*==============================================

	[XFile.h]
	Author : 出合翔太

===============================================*/

#pragma once
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

//#	XFileクラス：親クラス
/* XFileのロード、アンロードを管理するクラス */
class XFile
{
private:
	DWORD						MeshNum;				//	メッシュ数
	LPD3DXMESH					Mesh;					//	メッシュ
	D3DMATERIAL9				*pMeshMaterialList;		//	メッシュマテリアル
	LPDIRECT3DTEXTURE9			*pTextureList;			//	テクスチャリスト
	std::map<int, std::string> TextureNameList;			// テクスチャ名リスト
	static LPDIRECT3DDEVICE9	g_pD3Device;			//	デバイス
public:
	XFile():MeshNum(0),Mesh(NULL),pMeshMaterialList(NULL),pTextureList(NULL){}	//	コンストラクタ : 変数の初期値
	~XFile();							//	デストラクタ,モデルデータのアンロード
	bool Load(std::string fliename);	//	モデルデータのロード(引数：ファイル名)
	void Draw();						//	描画処理
};


