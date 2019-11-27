/*============================================

[Character.cpp]
Author :hohman yuushi

=============================================*/

#include "Character.h"
#include "Map.h"
#include "Model.h"
#include "input.h"
#include "main.h"
#include <d3dx9.h>
#include <math.h>
#include "Controller.h"
#include "XFile.h"


//	マクロ定義
#define FILELIST 1	//	読み込むファイルの数

/*--------------------------------------------------------------
enum
---------------------------------------------------------------*/
enum PLAYER_STATE		//g_Playerの状態遷移
{
	PLAYER_WAIT,		//	待機
	PLAYER_START,		//	開始
	PLAYER_ANSWER,		//	解答
	PLAYER_JUMP,		//	ジャンプ
	PLAYER_FINISH		//	終了(着地かな)
};


enum LANE_STATE			//レーンのなんかあれ
{
	LANE_START,


	LANE_SELECT,

	LANE_1,
	LANE_2,
	LANE_3,
	LANE_4,


	LANE_JUMP,

	LANE_END
};


/*---------------------------------------------------------------------------------
global
-----------------------------------------------------------------------------------*/
static HWND hWnd;				//メッセージ表示に使用

static int	g_LaneStatus;			//レーンステータス
static int	g_count;				//問題数カウンタ
static int	g_Q,g_A;				//正解番号格納、回答格納

static float		Speedtmp;					//SPEED一時保存


LPDIRECT3DDEVICE9 Character::g_pD3DDevice;

extern std::map<std::string, XFile *>g_pXFileList;

//static Model g_Player;

/*-----------------------------------------
関数諸々
-----------------------------------------*/
Character::Character()
{

}


Character::~Character()
{
	
}


void Character::Init()
{
	//!	XFlieのロード処理
	// 読み込みファイル名リスト
	std::string file_name_list[] =
	{
		"asset/model/ri.x",
	};

	// XFile読み込み
	for (int i = 0; i < FILELIST; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}

	//メッセージで利用してるから
	hWnd = GetHWND();
}


void Character::Uninit()
{

}


void Character::Update()
{
	CharacterCamera* p_CharCamera;
	p_CharCamera = GetCharCam();

	g_pD3DDevice = GetD3DDevice();
	// ワールド座標行列作成
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, position.x, position.y, position.z);
	D3DXMatrixRotationYawPitchRoll(&rot_matrix, angle.y, angle.x, angle.z);
	D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, scale.y);

	world_matrix *= rot_matrix * trans_matrix;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if (pmodel != NULL)
	{
		pmodel->Draw();
	}

	//p_CharCamera->Init = D3DXVECTOR3(position.x, position.y, position.z);
	//p_CharCamera->Init = D3DXVECTOR3(position.x, position.y, position.z);

	if (KeyBoard::IsTrigger(DIK_W))
	{
		position.y += 1.0f;
		position.z += 1.0f;
	}
}


void Character::Draw()
{
}
