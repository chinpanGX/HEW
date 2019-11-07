/*==========================================================

	[Field.cpp]
	Author : 出合翔太

===========================================================*/

#include "Field.h"
#include "Model.h"
#include "Drawer.h"

extern std::map<std::string, Model *>g_pXFileList;	// 読み込んだXFileのリスト

void Field::Load()
{
	// XFile読み込み
	for (int i = 0; i < 2; i++)
	{
		g_pXFileList[file_name_list[i]] = new Model();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}
}

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
	Drawer sample(
		D3DXVECTOR3(3.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["ri.x"]);
	
}



