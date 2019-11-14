/*========================================================
	
	[Map.cpp]
	Author : 出合翔太

=========================================================*/

#include <map>
#include "main.h"
#include "Map.h"

//	マクロ定義
#define FILELIST 2	//	読み込むファイルの数

//	グローバル変数
extern std::map<std::string, XFile *>g_pXFileList;	//	XFileのリスト
Model *Map::Actor[ACTOR_NUM];						//	Model型ポインタ配列
Field *Map::pField[1];								//	Field型ポインタ

void Map::Init()
{
	//!	XFlieのロード処理
	// 読み込みファイル名リスト
	const std::string file_name_list[] =
	{
		"asset/model/ri.x",
	};

	// XFile読み込み
	for (int i = 0; i < FILELIST; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();				//	XFileを格納するメモリの確保
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);	//	ロード関数の呼び出し
	}
	
	//pField[0] = new Field;

	//pField[0]->Init();
}

//	マップの終了処理
void Map::Uninit()
{
	//!	メモリ解放を忘れないようにする
	//delete pField[0];
	delete Actor[0];	
}

//	マップの描画(3Dモデルの配置、描画)
void Map::Draw()
{
	
	Actor[0] = new Model(D3DXVECTOR3(0.0f, 0.0f, -10.0f),D3DXVECTOR3(1.0f, 1.0f, 1.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f),g_pXFileList["asset/model/ri.x"]);
	Actor[0]->Draw();


	//pField[0]->Draw();
}
