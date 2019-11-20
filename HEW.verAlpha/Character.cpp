/*============================================

	[Character.cpp]
	Author :　

=============================================*/

#include "main.h"
#include "Character.h"

extern std::map<std::string, XFile *>g_pXFileList;
Model *Character::Actor[1];

void Character::Init()
{
	//!	XFlieのロード処理
	// 読み込みファイル名リスト
	std::string file_name_list[] =
	{
		"asset/model/ri.x",
		//"asset/modeldai.x",
	};

	// XFile読み込み
	for (int i = 0; i < 1; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}
	
	Actor[0] = new Model(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_pXFileList["asset/model/ri.x"]);
}

void Character::Uninit()
{
	
}

void Character::Update()
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

void Character::Draw()
{

}

