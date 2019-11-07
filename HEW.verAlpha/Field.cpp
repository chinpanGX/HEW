/*==========================================================

	[Field.cpp]
	Author : 出合翔太

===========================================================*/

#include <map>
#include "Field.h"
#include "Model.h"
#include "XFile.h"

//	グローバル変数
extern std::map<std::string, XFile *>g_pXFileList;	// 読み込んだXFileのリスト

//	マップのロード
void Field::Load()
{
	// XFile読み込み
	for (int i = 0; i < 1; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}
}

//	マップの描画
void Field::Draw()
{
	//描画サンプル
#if 0 
	// XFileオブジェクト作成
	Drawer obj1(
		D3DXVECTOR3(3.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["Sample01.x"]);
#endif
	Model sample(
		D3DXVECTOR3(3.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["ri.x"]);
	
}



