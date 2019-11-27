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
extern std::map<std::string, XFile *>g_pXFileList;

//	初期化処理
void Map::Init()
{
	//!	XFlieのロード処理
	// 読み込みファイル名リスト
	std::string file_name_list[] =
	{
		"asset/model/ri.x",
		"asset/model/dai.x",
	};

	// XFile読み込み
	for (int i = 0; i < FILELIST; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}

	//	インスタンス生成、メモリの動的確保 (引数：位置、大きさ、回転、読み込むファイル名)
	m_Actor[0] = new Model (D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_pXFileList["asset/model/dai.x"]);
}

//	終了処理
void Map::Uninit()
{
	//	ヒープ領域のメモリを解放
	delete m_Actor[0];
}

//	描画処理
void Map::Draw()
{
	m_Actor[0]->Draw();	//	ジャンプの描画
}
