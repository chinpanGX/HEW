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


#define	VALUE_MOVE		(5.0f)							// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// 回転量


#define	NUM_VERTEX		(60)		// 頂点数
#define	NUM_POLYGON		(24)		// ポリゴン数


#define	BOX_WIDTH		(100.0f)						// 地面の幅(X方向)
#define	BOX_DEPTH		(100.0f)						// 地面の奥行(Z方向)
#define BOX_HEIGHT		(100.0f)						//地面　（Y方向）

#define NUM_BOX			(2)								// 

/*--------------------------------------------------------------
enum
---------------------------------------------------------------*/
enum PLAYER_STATE		//Playerの状態遷移
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
struct
---------------------------------------------------------------------------------*/
typedef struct
{
	D3DXVECTOR3 PPos;		//PlayerPoint(postion)
	float		P_x, P_y;	//Playerにかかる移動量
	float		Speed;		//Playerの速度
	int			Status;		//Playerの状態
}PlayerData;


/*---------------------------------------------------------------------------------
global
-----------------------------------------------------------------------------------*/
static PlayerData g_Player;		//プレイヤーデータ
static HWND hWnd;				//メッセージ表示に使用

static int	g_LaneStatus;			//レーンステータス
static int	g_count;				//問題数カウンタ
static int	g_Q,g_A;				//正解番号格納、回答格納

static float		tmp;					//SPEED一時保存



CGraphic*				glbl_graphic = NULL;

LPDIRECT3D9				g_pD3D = NULL;			//D3Dインターフェース D3Dデバイスを作るのに必要
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;	//D3Dデバイス 描画など広範囲で必要になる。
IDirect3DVertexBuffer9* g_pVB = NULL;			//ポリゴンのバッファ



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
	//とりあえずここで初期化
	g_Player.PPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_Player.PVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.Speed = 0;
	g_Player.Status = PLAYER_WAIT;

	//メッセージで利用してるから
	hWnd = GetHWND();


}


void Character::Uninit()
{
	
}


void Character::Update()
{
	////Playerのステータスで判断(ステータス外の数値はエラー対応)
	//switch (g_Player.Status)
	//{
	//	//待機モーションでも垂れ流しときゃええんちゃう？
	//case PLAYER_WAIT:

	//	//ここにモーションかな

	//	if (Input::KB_IsTrigger(DIK_E))
	//	{
	//		//ステータス変更
	//		g_Player.Status = PLAYER_START;
	//	}
	//	break;

	//	
	//case PLAYER_START:		//滑走開始

	//	if (g_Player.Speed >= 5.0f)
	//	{
	//		tmp = g_Player.Speed;

	//		//ここにちょっとインターバル入れればいいかな
	//		g_Player.Status = PLAYER_ANSWER;
	//	}

	//	//加速
	//	g_Player.Speed += 0.2f;

	//	break;

	//	
	//case PLAYER_ANSWER:		//解答

	//	//SPEEDを保存して停止
	//	tmp = g_Player.Speed;
	//	g_Player.Speed = 0.0f;

	//if (Input::KB_IsTrigger(DIK_A))
	//{// 左移動

	//}
	//else if (Input::KB_IsTrigger(DIK_D))
	//{// 右移動

	//}

	////とりあえずSpaceで次へ
	//if (Input::KB_IsTrigger(DIK_SPACE))
	//{
	//	//何回回答したか
	//	g_count++;

	//	//速度復元
	//	g_Player.Speed = tmp;

	//	if (g_Q == g_A)
	//	{
	//		g_Player.Speed *= 0.3f;
	//	}
	//	
	//	if (g_count >= 3)
	//	{
	//		g_Player.Status = PLAYER_JUMP;
	//	}
	//	else
	//	{
	//		g_Player.Status = PLAYER_START;
	//	}
	//}
	//	break;



	//	case PLAYER_JUMP:		//ジャンプ

	//	//加速、タイミングの兼ね合いで数値を出す
	//	MessageBox(hWnd, "Jump処理", "JUMP", MB_OK);	//...指標(台)がないとタイミングとれなくね
	//	g_Player.Status = PLAYER_FINISH;

	//	break;

	//	
	//case PLAYER_FINISH:		//終了

	//	MessageBox(hWnd, "終了処理", "END", MB_OK);

	//	break;


	//default:
	//	//エラー対応
	//	MessageBox(hWnd, "存在しないプレイヤーステータスです", "ERROR", MB_OK);
	//	exit(1);

	//	break;
	//}


			
}

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBox(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	// 頂点バッファへのポインタ
static LPDIRECT3DINDEXBUFFER9	g_pIdxBuffField = NULL;
static int						g_NumIndexField = 36;

typedef struct
{
	D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス
	D3DXVECTOR3				g_posField;				// 地面の位置
	D3DXVECTOR3				g_rotField;				// 地面の向き(回転)
	D3DXVECTOR3				g_sclField;				// 地面の大きさ(スケール)
}BOX_T;

static BOX_T g_Box[NUM_BOX];

static float g_move_x = 0.01f;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Box_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// 頂点情報の作成
	MakeVertexBox(pDevice);

	//// 位置・回転・スケールの初期設定
	//g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_sclField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Box_Finalize(void)
{
	if (g_pIdxBuffField != NULL)
	{//
		g_pIdxBuffField->Release();
		g_pIdxBuffField = NULL;
	}


	if (g_pVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Box_Update(void)
{

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//ワールドマトリックスの初期化
	for (int i = 0; i < NUM_BOX; i++)
	{
		D3DXMatrixIdentity(&g_Box[i].g_mtxWorldField);
	}

	//g_Box[0].g_rotField.y += 0.05f;

	//回転を反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[0].g_rotField.y, g_Box[0].g_rotField.x, g_Box[0].g_rotField.z);
	//D3DXMatrixMultiply(&g_Box[0].g_mtxWorldField, &g_Box[0].g_mtxWorldField, &mtxRot);

	//g_Box[0].g_posField.x = 100.0f;
	//g_Box[0].g_posField.y = 0.0f;
	//g_Box[0].g_posField.z = 100.0f;

	//移動を反映
	//D3DXMatrixTranslation(&mtxTranslate, g_Box[0].g_posField.x, g_Box[0].g_posField.y, g_Box[0].g_posField.z);
	//D3DXMatrixMultiply(&g_Box[0].g_mtxWorldField, &g_Box[0].g_mtxWorldField, &mtxTranslate);


	//g_Box[1].g_posField.x = 100.0f;
	//g_Box[1].g_posField.y = 0.0f;
	//g_Box[1].g_posField.z = 100.0f;

	//移動を反映
	//D3DXMatrixTranslation(&mtxTranslate, g_Box[1].g_posField.x, g_Box[1].g_posField.y, g_Box[1].g_posField.z);
	//D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxTranslate);

	//g_Box[1].g_rotField.y += 0.05f;

	//回転を反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, -g_Box[1].g_rotField.y, g_Box[1].g_rotField.x, g_Box[1].g_rotField.z);
	//D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxRot);

	//g_Box[1].g_posField.x += 100.0f;
	//g_Box[1].g_posField.z += 100.0f;

	//移動を反映
	//D3DXMatrixTranslation(&mtxTranslate, g_Box[1].g_posField.x, g_Box[1].g_posField.y, g_Box[1].g_posField.z);
	//D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxTranslate);

	//回転を反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Box[1].g_rotField.y, g_Box[1].g_rotField.x, g_Box[1].g_rotField.z);
	//D3DXMatrixMultiply(&g_Box[1].g_mtxWorldField, &g_Box[1].g_mtxWorldField, &mtxRot);

	////スケールを反映
	//D3DXMatrixScaling(&mtxScl, g_sclField.x, g_sclField.y, g_sclField.z);
	//D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);




		if (KeyBoard::IsPress(DIK_A))
		{
			if (KeyBoard::IsPress(DIK_W))
			{// 左奥移動
				g_Box[0].g_posField.x += sinf(-D3DX_PI * 0.75f) * VALUE_MOVE;
				g_Box[0].g_posField.z -= cosf(-D3DX_PI * 0.75f) * VALUE_MOVE;
			}
			else if (KeyBoard::IsPress(DIK_S))
			{// 左手前移動
				g_Box[0].g_posField.x += sinf(-D3DX_PI * 0.25f) * VALUE_MOVE;
				g_Box[0].g_posField.z -= cosf(-D3DX_PI * 0.25f) * VALUE_MOVE;
			}
			else
			{// 左移動
				g_Box[0].g_posField.x += sinf(-D3DX_PI * 0.50f) * VALUE_MOVE;
				g_Box[0].g_posField.z -= cosf(-D3DX_PI * 0.50f) * VALUE_MOVE;
			}
		}
		else if (KeyBoard::IsPress(DIK_D))
		{
			if (KeyBoard::IsPress(DIK_W))
			{// 右奥移動
				g_Box[0].g_posField.x += sinf(D3DX_PI * 0.75f) * VALUE_MOVE;
				g_Box[0].g_posField.z -= cosf(D3DX_PI * 0.75f) * VALUE_MOVE;
			}
			else if (KeyBoard::IsPress(DIK_S))
			{// 右手前移動
				g_Box[0].g_posField.x += sinf(D3DX_PI * 0.25f) * VALUE_MOVE;
				g_Box[0].g_posField.z -= cosf(D3DX_PI * 0.25f) * VALUE_MOVE;
			}
			else
			{// 右移動
				g_Box[0].g_posField.x += sinf(D3DX_PI * 0.50f) * VALUE_MOVE;
				g_Box[0].g_posField.z -= cosf(D3DX_PI * 0.50f) * VALUE_MOVE;
			}
		}
		else if (KeyBoard::IsPress(DIK_W))
		{// 奥移動
			g_Box[0].g_posField.x += sinf(D3DX_PI * 1.0f) * VALUE_MOVE;
			g_Box[0].g_posField.z -= cosf(D3DX_PI * 1.0f) * VALUE_MOVE;
		}
		else if (KeyBoard::IsPress(DIK_S))
		{// 手前移動
			g_Box[0].g_posField.x += sinf(D3DX_PI * 0.0f) * VALUE_MOVE;
			g_Box[0].g_posField.z -= cosf(D3DX_PI * 0.0f) * VALUE_MOVE;
		}
	
	#if 1
		if (KeyBoard::IsPress(DIK_Q))
		{// Y軸左回転
			g_Box[0].g_rotField.y -= VALUE_ROTATE;
			if(g_Box[0].g_rotField.y > D3DX_PI)
			{
				g_Box[0].g_rotField.y -= D3DX_PI * 2.0f;
			}
			if(g_Box[0].g_rotField.y < -D3DX_PI)
			{
				g_Box[0].g_rotField.y += D3DX_PI * 2.0f;
			}
		}
		if (KeyBoard::IsPress(DIK_E))
		{// Y軸右回転
			g_Box[0].g_rotField.y += VALUE_ROTATE;
			if(g_Box[0].g_rotField.y > D3DX_PI)
			{
				g_Box[0].g_rotField.y -= D3DX_PI * 2.0f;
			}
			if(g_Box[0].g_rotField.y < -D3DX_PI)
			{
				g_Box[0].g_rotField.y += D3DX_PI * 2.0f;
			}
		}
	#endif
	
	#if 1
		if (KeyBoard::IsPress(DIK_UP))
		{// X軸右回転
			g_Box[0].g_rotField.x += VALUE_ROTATE;
			if(g_Box[0].g_rotField.x > D3DX_PI)
			{
				g_Box[0].g_rotField.x -= D3DX_PI * 2.0f;
			}
			if(g_Box[0].g_rotField.x < -D3DX_PI)
			{
				g_Box[0].g_rotField.x += D3DX_PI * 2.0f;
			}
		}
		if (KeyBoard::IsPress(DIK_DOWN))
		{// X軸左回転
			g_Box[0].g_rotField.x -= VALUE_ROTATE;
			if(g_Box[0].g_rotField.x > D3DX_PI)
			{
				g_Box[0].g_rotField.x -= D3DX_PI * 2.0f;
			}
			if(g_Box[0].g_rotField.x < -D3DX_PI)
			{
				g_Box[0].g_rotField.x += D3DX_PI * 2.0f;
			}
		}
	#endif
	
	#if 1
		if (KeyBoard::IsPress(DIK_LEFT))
		{// Z軸右回転
			g_Box[0].g_rotField.z += VALUE_ROTATE;
			if(g_Box[0].g_rotField.z > D3DX_PI)
			{
				g_Box[0].g_rotField.z -= D3DX_PI * 2.0f;
			}
			if(g_Box[0].g_rotField.z < -D3DX_PI)
			{
				g_Box[0].g_rotField.z += D3DX_PI * 2.0f;
			}
		}
		if (KeyBoard::IsPress(DIK_RIGHT))
		{// Z軸左回転
			g_Box[0].g_rotField.z -= VALUE_ROTATE;
			if(g_Box[0].g_rotField.z > D3DX_PI)
			{
				g_Box[0].g_rotField.z -= D3DX_PI * 2.0f;
			}
			if(g_Box[0].g_rotField.z < -D3DX_PI)
			{
				g_Box[0].g_rotField.z += D3DX_PI * 2.0f;
			}
		}
	#endif
	
		if (KeyBoard::IsPress(DIK_RETURN))
		{// リセット
			g_Box[0].g_posField.x = 0.0f;
			g_Box[0].g_posField.y = 0.0f;
			g_Box[0].g_posField.z = 0.0f;
	
			g_Box[0].g_rotField.x = 0.0f;
			g_Box[0].g_rotField.y = 0.0f;
			g_Box[0].g_rotField.z = 0.0f;
		}

	/*DebugProc_Print((char*)"*** ３Ｄポリゴン操作 ***\n");
	DebugProc_Print((char*)"位置 [%f : %f : %f]\n", g_posField.x, g_posField.y, g_posField.z);
	DebugProc_Print((char*)"前移動 : Ｗ\n");
	DebugProc_Print((char*)"後移動 : Ｓ\n");
	DebugProc_Print((char*)"左移動 : Ａ\n");
	DebugProc_Print((char*)"右移動 : Ｄ\n");
	DebugProc_Print((char*)"\n");

	DebugProc_Print((char*)"向き [%f : %f : %f]\n", g_rotField.x, g_rotField.y, g_rotField.z);
	DebugProc_Print((char*)"X軸回転 : ↑ / ↓\n");
	DebugProc_Print((char*)"Y軸回転 : Ｑ / Ｅ\n");
	DebugProc_Print((char*)"Z軸回転 : ← / →\n");
	DebugProc_Print((char*)"\n");

	DebugProc_Print((char*)"位置.向きリセット : ENTER\n");*/
}

//=============================================================================
// 描画処理
//=============================================================================
void Box_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();


	for (int i = 0; i < NUM_BOX; i++)
	{
		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Box[i].g_mtxWorldField);

		//頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		//インデックスバッファのセット
		pDevice->SetIndices(g_pIdxBuffField);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_NumIndexField, 0, 12);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBox(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL)))
	{
		return E_FAIL;
	}
	{
		VERTEX_3D *pVtx;

		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		//WIDTH　X軸　HEIGHT Y軸 DEPTH Z軸

		////上面
		//pVtx[0].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);
		//pVtx[1].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);
		//pVtx[2].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT,-BOX_DEPTH);
		//pVtx[3].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);
		//pVtx[4].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);
		//pVtx[5].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);

		////下面
		//pVtx[6].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);
		//pVtx[7].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT,BOX_DEPTH);
		//pVtx[8].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT,-BOX_DEPTH);
		//pVtx[9].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT,-BOX_DEPTH);
		//pVtx[10].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT,-BOX_DEPTH);
		//pVtx[11].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);

		////奥面
		//pVtx[12].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);
		//pVtx[13].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);
		//pVtx[14].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);
		//pVtx[15].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);
		//pVtx[16].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);
		//pVtx[17].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);

		////右面
		//pVtx[18].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);
		//pVtx[19].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);
		//pVtx[20].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT,-BOX_DEPTH);
		//pVtx[21].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);
		//pVtx[22].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);
		//pVtx[23].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT, -BOX_DEPTH);

		////左面
		//pVtx[24].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);
		//pVtx[25].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);
		//pVtx[26].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);
		//pVtx[27].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);
		//pVtx[28].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT, -BOX_DEPTH);
		//pVtx[29].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);

		////正面
		//pVtx[30].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);
		//pVtx[31].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);
		//pVtx[32].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT,-BOX_DEPTH);
		//pVtx[33].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);
		//pVtx[34].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT,-BOX_DEPTH);
		//pVtx[35].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT,-BOX_DEPTH);
		//
		////法線ベクトルの設定
		//pVtx[0].nor = D3DXVECTOR3( 0.0f,1.0f, 0.0f);
		//pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
		//pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
		//pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
		//pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//
		//pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[14].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[15].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[16].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[17].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//pVtx[18].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[19].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[20].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[21].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[22].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[23].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//pVtx[24].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[25].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[26].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[27].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[28].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[29].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//pVtx[30].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[31].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[32].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[33].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[34].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[35].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		////頂点カラーの設定
		//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[28].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[29].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//pVtx[30].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[31].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[32].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[33].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[34].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[35].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////テクスチャ座標の設定
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		//pVtx[4].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);

		//pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[9].tex = D3DXVECTOR2(1.0f, 1.0f);
		//pVtx[10].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[11].tex = D3DXVECTOR2(0.0f, 0.0f);

		//pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);
		//pVtx[16].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[17].tex = D3DXVECTOR2(0.0f, 0.0f);

		//pVtx[18].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[19].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[20].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[21].tex = D3DXVECTOR2(1.0f, 1.0f);
		//pVtx[22].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[23].tex = D3DXVECTOR2(0.0f, 0.0f);

		//pVtx[24].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[25].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[26].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[27].tex = D3DXVECTOR2(1.0f, 1.0f);
		//pVtx[28].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[29].tex = D3DXVECTOR2(0.0f, 0.0f);

		//pVtx[30].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[31].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[32].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[33].tex = D3DXVECTOR2(1.0f, 1.0f);
		//pVtx[34].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[35].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx[0].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, -BOX_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT, -BOX_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT, -BOX_DEPTH);
		pVtx[4].pos = D3DXVECTOR3(BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);
		pVtx[5].pos = D3DXVECTOR3(-BOX_WIDTH, -BOX_HEIGHT, BOX_DEPTH);
		pVtx[6].pos = D3DXVECTOR3(BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);
		pVtx[7].pos = D3DXVECTOR3(-BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH);

		pVtx[0].nor = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
		pVtx[5].nor = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
		pVtx[6].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[7].nor = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_pVtxBuffField->Unlock();
	}

	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * 8,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffField,
		NULL)))
	{
		return E_FAIL;
	}

	{
		WORD *pIdx;

		g_pIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);

		//前面
		pIdx[0] = 4;
		pIdx[1] = 1;
		pIdx[2] = 5;
		pIdx[3] = 1;
		pIdx[4] = 6;
		pIdx[5] = 2;


		pIdx[6] = 7;
		pIdx[7] = 3;
		pIdx[8] = 0;
		pIdx[9] = 6;
		pIdx[10] = 1;
		pIdx[11] = 0;

		//右
		pIdx[12] = 1;
		pIdx[13] = 6;
		pIdx[14] = 3;
		pIdx[15] = 6;
		pIdx[16] = 4;
		pIdx[17] = 3;

		//下
		pIdx[18] = 3;
		pIdx[19] = 2;
		pIdx[20] = 4;
		pIdx[21] = 2;
		pIdx[22] = 5;
		pIdx[23] = 4;

		//左
		pIdx[24] = 2;
		pIdx[25] = 5;
		pIdx[26] = 0;
		pIdx[27] = 7;
		pIdx[28] = 0;
		pIdx[29] = 5;

		//背面
		pIdx[30] = 5;
		pIdx[31] = 4;
		pIdx[32] = 7;
		pIdx[33] = 6;
		pIdx[34] = 7;
		pIdx[35] = 4;

		g_pIdxBuffField->Unlock();
	}


	return S_OK;

}


void Character::Draw()
{
}
